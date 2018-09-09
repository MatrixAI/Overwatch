# Source: https://github.com/iovisor/bcc/blob/master/examples/networking/http_filter/

#!/usr/bin/python
#
#Bertrone Matteo - Polytechnic of Turin
#November 2015
#
#eBPF application that parses HTTP packets
#and extracts (and prints on screen) the URL contained in the GET/POST request.
#
#eBPF program http_filter is used as SOCKET_FILTER attached to eth0 interface.
#only packet of type ip and tcp containing HTTP GET/POST are returned to userspace, others dropped
#
#python script uses bcc BPF Compiler Collection by iovisor (https://github.com/iovisor/bcc)
#and prints on stdout the first line of the HTTP GET/POST request containing the url

from __future__ import print_function
from bcc import BPF
from sys import argv

import atexit
import ctypes as ct
import sys
import socket
import struct
import os

#args
def usage():
    print("USAGE: %s [-i <if_name>]" % argv[0])
    print("")
    print("Try '%s -h' for more options." % argv[0])
    exit()

#help
def help():
    print("USAGE: %s [-i <if_name>]" % argv[0])
    print("")
    print("optional arguments:")
    print("   -h                       print this help")
    print("   -i if_name               select interface if_name. Default is lo")
    print("")
    print("examples:")
    print("    http-parse              # bind socket to eth0")
    print("    http-parse -i wlan0     # bind socket to wlan0")
    exit()

#print bpf output
def print_http_exc(cpu, data, size):
    class Data(ct.Structure):
        _fields_ =  [ ("src_ip", ct.c_uint32),
                      ("dst_ip", ct.c_uint32),
                      ("src_port", ct.c_ushort),
                      ("dst_port", ct.c_ushort),
                      ("proc_time", ct.c_uint64) ]

    http_exc = ct.cast(data, ct.POINTER(SkbEvent)).contents
    print('src {}:{}; dst {}:{}; proc_time: {}'
          .format(http_exc.src_ip, http_exc.src_port, http_exc.dst_ip,
                  http_exc.dst_port, http_exc.proc_time))

#arguments
interface="lo"

if len(argv) == 2:
  if str(argv[1]) == '-h':
    help()
  else:
    usage()

if len(argv) == 3:
  if str(argv[1]) == '-i':
    interface = argv[2]
  else:
    usage()

if len(argv) > 3:
  usage()

print ("binding socket to '%s'" % interface)

# initialize BPF - load source code from http-parse-simple.c
bpf = BPF(src_file="monitorHttp.c", debug=0)

#load eBPF program http_filter of type SOCKET_FILTER into the kernel eBPF vm
#more info about eBPF program types
#http://man7.org/linux/man-pages/man2/bpf.2.html
function_http_filter = bpf.load_func("http_filter", BPF.SOCKET_FILTER)

#create raw socket, bind it to interface
#attach bpf program to socket created
BPF.attach_raw_socket(function_http_filter, interface)

#get file descriptor of the socket previously created inside BPF.attach_raw_socket
socket_fd = function_http_filter.sock

#create python socket object, from the file descriptor
sock = socket.fromfd(socket_fd,socket.PF_PACKET,socket.SOCK_RAW,socket.IPPROTO_IP)
#set it as blocking socket
sock.setblocking(True)

# bpf["events"].open_perf_buffer(print_http_exc)

@atexit.register
def print_results():
    # counter prints
    counters = bpf['counters'].values()
    print("# of requests: {}; # of responses: {}".format(counters[0].value, counters[1].value))
    print("# of elapsed times: {}".format(counters[2].value))

    # logs
    logs = bpf['logs']
    for k, v in sorted(logs.items(), key=lambda logs : logs[0].value):
        print("timestamp: {} ns; src {}:{}; dst {}:{}"
              .format(k.value, socket.inet_ntoa(struct.pack("!I", v.src_ip)), v.src_port,
                      socket.inet_ntoa(struct.pack("!I", v.dst_ip)), v.dst_port))

    # latency prints
    records = bpf['records'].values()
    for rec in records:
        print(rec)


while 1:
  # bpf.perf_buffer_poll()
  #retrieve raw packet from socket
  packet_str = os.read(socket_fd,2048)

  #DEBUG - print raw packet in hex format
  #packet_hex = toHex(packet_str)
  #print ("%s" % packet_hex)

  #convert packet into bytearray
  packet_bytearray = bytearray(packet_str)

  #ethernet header length
  ETH_HLEN = 14

  #IP HEADER
  #https://tools.ietf.org/html/rfc791
  # 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
  # +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  # |Version|  IHL  |Type of Service|          Total Length         |
  # +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  #
  #IHL : Internet Header Length is the length of the internet header
  #value to multiply * 4 byte
  #e.g. IHL = 5 ; IP Header Length = 5 * 4 byte = 20 byte
  #
  #Total length: This 16-bit field defines the entire packet size,
  #including header and data, in bytes.

  #calculate packet total length
  total_length = packet_bytearray[ETH_HLEN + 2]               #load MSB
  total_length = total_length << 8                            #shift MSB
  total_length = total_length + packet_bytearray[ETH_HLEN+3]  #add LSB

  #calculate ip header length
  ip_header_length = packet_bytearray[ETH_HLEN]               #load Byte
  ip_header_length = ip_header_length & 0x0F                  #mask bits 0..3
  ip_header_length = ip_header_length << 2                    #shift to obtain length

  #TCP HEADER
  #https://www.rfc-editor.org/rfc/rfc793.txt
  #  12              13              14              15
  #  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
  # +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  # |  Data |           |U|A|P|R|S|F|                               |
  # | Offset| Reserved  |R|C|S|S|Y|I|            Window             |
  # |       |           |G|K|H|T|N|N|                               |
  # +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  #
  #Data Offset: This indicates where the data begins.
  #The TCP header is an integral number of 32 bits long.
  #value to multiply * 4 byte
  #e.g. DataOffset = 5 ; TCP Header Length = 5 * 4 byte = 20 byte

  #calculate tcp header length
  tcp_header_length = packet_bytearray[ETH_HLEN + ip_header_length + 12]  #load Byte
  tcp_header_length = tcp_header_length & 0xF0                            #mask bit 4..7
  tcp_header_length = tcp_header_length >> 2                              #SHR 4 ; SHL 2 -> SHR 2

  #calculate payload offset
  payload_offset = ETH_HLEN + ip_header_length + tcp_header_length

  #print first line of the HTTP GET/POST request
  #line ends with 0xOD 0xOA (\r\n)
  #(if we want to print all the header print until \r\n\r\n)
  for i in range (payload_offset-1,len(packet_bytearray)-1):
    if (packet_bytearray[i]== 0x0A):
      if (packet_bytearray[i-1] == 0x0D):
        break
    print ("%c" % chr(packet_bytearray[i]), end = "")
  print("")

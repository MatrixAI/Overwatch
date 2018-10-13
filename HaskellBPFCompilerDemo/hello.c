#include <stdio.h>
#include <unistd.h>
/* libbcc */
#include <bcc/bpf_common.h>
#include <bcc/libbpf.h>

// #include <linux/bpf.h>

const char *bpf_text = " \
ssize_t hello(struct __sk_buff *skb)	\
{						\
	return 0;		\
}						\
";

// void * bpf_module_create_c_from_string(const char *text, unsigned flags, const char *cflags[], int ncflags);
// void bpf_module_destroy(void *program);

int main(){
  void *mod = bpf_module_create_c_from_string(bpf_text, 0, NULL, 0);
	// int fd = bpf_prog_load(
  //   BPF_PROG_TYPE_SOCKET_FILTER,
  //   "sample_prog",
	// 	bpf_function_start(mod, "bpf_prog1"),
	// 	bpf_function_size(mod, "bpf_prog1"),
	// 	bpf_module_license(mod),
	// 	bpf_module_kern_version(mod),
  //   0, NULL, 0);
  //
  // const char *if_name = "vth0";
  // int sock_fd = bpf_open_raw_sock(if_name);
  // bpf_attach_socket(sock_fd, fd);
  //
  // printf("BPF program attached to %s\n", if_name);
  // printf("Press any key to quit");
  // getchar();
  //
  // close(sock_fd);
  // close(fd);
  bpf_module_destroy(mod);
  return 0;
}

# 23/2/2018 - 1/3/2018 Summary

## Workload Types

Typically, we can divide tasks into those that are more computational and those that are more request handlers. There are other types too, which are worth reading into, but these two are the most used in literature.

## Latency Requirements

A request handler needs to handle requests quickly. One of the best ways to specify a constraint on this is using percentiles. Using other statistical measurements will lead to statistical biases. Note that since websites can result in hundreds of requests, having 99% of requests be quick isn't good enough, since most website requests will result in a query slower than the 99%. Definitely set a constraint on 100% of queries, and consider setting one on 99.9% or more.

Also, when monitoring the latency, make sure to measure from when a query is received, not from when it starts being processed.

Heatmaps are a good way to visualise latency clearly, and to store data about latency efficiently.

The way we monitor latency depends on the exact implementation of containers, but should be possible in any setup.

## Computation Requirements

One way that computational tasks are constrained is by waiting time and execution time. Most papers seem to indicate that workloads will report how far through a computation they are, allowing for their resources to be tweaked.

Some papers suggested merely monitoring CPU calculations per second as a way of measuring service, setting some constraint of atleast 95% the maximum speed of the processor.

## General Ideas

Test the monitoring system on artifical scenarios, to check the results match the behaviour.

## Distributed Systems

A lot of design decisions go into making any sort of distributed system. These will have to be considered at some point.

## Monitoring Tools

There is a monitoring tool for everything.

### BPF

BPF can be used to run platform independent code in the live kernel. bcc is a tool for writing BPF programs.

## Downtime

Downtime seems a useful metric to keep track of, as it will be easy to predict the downtime of various possible setups. There are various ways to estimate downtime of an unknown system, though more reading on the topic is suggested.

## Profiling Workloads

Quasar, Paragon, ARQ and other technologies use small amounts of data obtained in seconds of benchmarking, combined with a large amount of records from previous workloads, to statistically categorise incoming workloads and put them on the correct server. The techniques involved stem from linear algebra.

These techniques were only shown to keep workloads with a single constraint (completion/time) maximised, but might be adaptable to situations with more requirements. They argue that the profiling introduced minimal overhead (more reading will probably provide a more convincing argument of this).

## Dominant Resource Fairness

This is a technique where, given the ratio of resources each workload needs, and an optional weight to each workload, the entire resources will be given in a fair manner to each workload. It is designed to have certain properties, including always giving each workload atleast as many resources as if it just took a proportion of every resource, and disadvantaging workloads that give inaccurate ratios.

This is a simple solution, but relies on workloads having accurate ratios of the resources they will need. It also doesn't specify a continuous algorithm, which would be ideal, nor does it state one does not exist, though applying the discrete algorithms on small enough blocks will provide a decent approximation.

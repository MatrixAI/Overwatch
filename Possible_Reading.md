# Future Reading

## Monitoring Tools

### Unread

* Wireshark https://www.wireshark.org/
* System Tap https://sourceware.org/systemtap/wiki
* https://github.com/iovisor/bcc
* riemann http://riemann.io/
* http://serverfault.com/questions/523351/how-do-statsd-and-collectd-relate
* http://en.wikipedia.org/wiki/Profiling_%28computer_programming%29
    * Reference 8
* http://jasonwilder.com/blog/2012/01/03/centralized-logging/
* http://jasonwilder.com/blog/2013/07/16/centralized-logging-architecture/
* http://fractio.nl/2014/05/10/rethinking-monitoring/
* http://fractio.nl/2014/02/12/data-driven-alerting-with-flapjack-puppet-hiera/
* http://en.wikipedia.org/wiki/Consilience
* http://misfra.me/state-of-the-state-part-iii
* https://qmonnet.github.io/whirl-offload/2016/09/01/dive-into-bpf/
* https://github.com/google/cadvisor
* Check out grafana as well
* https://blog.yadutaf.fr/2017/07/28/tracing-a-packet-journey-using-linux-tracepoints-perf-ebpf/
* OpenTracing - see zipkin and dapper (there are papers on these)
* http://www.brendangregg.com/blog/2015-09-22/bcc-linux-4.3-tracing.html
* https://github.com/google/stenographer - this looks really useful for capturing lots of packets

### Read Later

* http://www.brendangregg.com/blog/2015-07-08/choosing-a-linux-tracer.html
* https://news.ycombinator.com/item?id=8450147 (looks of good opinions here!)

## Monitoring Theory

### Unread

* http://sam-koblenski.blogspot.com.au/2015/08/everyday-dsp-for-programmers-basic.html
* http://www.diku.dk/OLD/undervisning/2005v/347/p121-joyce.pdf
* http://ieeexplore.ieee.org/xpl/login.jsp?tp=&arnumber=1703189&url=http%3A%2F%2Fieeexplore.ieee.org%2Fiel5%2F11167%2F35938%2F01703189.pdf%3Farnumber%3D1703189
* http://ieeexplore.ieee.org/xpl/login.jsp?tp=&arnumber=5984319&url=http%3A%2F%2Fieeexplore.ieee.org%2Fxpls%2Fabs_all.jsp%3Farnumber%3D5984319
* http://arxiv.org/ftp/arxiv/papers/1204/1204.0179.pdf
* http://en.wikipedia.org/wiki/Distributed_control_system
* http://en.wikipedia.org/wiki/Network_traffic_measurement
* http://en.wikipedia.org/wiki/Teletraffic_engineering
* Bernoulli Sampling
* https://github.com/umbrant/QuantileEstimation
* http://marios.io/2010/03/02/stream-algorithms-order-statistics/
* http://nuit-blanche.blogspot.com.au/2014/01/frugal-streaming-and-sparse-recovery.html?m=1
* https://en.wikipedia.org/wiki/Unevenly_spaced_time_series

### Read Later

* http://www.lsv.ens-cachan.fr/Publis/PAPERS/PDF/AMB-icde08.pdf
* http://www.nt.ntnu.no/users/skoge/prost/proceedings/adchem09/cd/abstract/78.pdf
* http://digitalcommons.calpoly.edu/cgi/viewcontent.cgi?article=1013&context=csse_fac

## Language Semantics

* https://en.wikipedia.org/wiki/Constraint_logic_programming
* (read) https://en.wikipedia.org/wiki/Linear_temporal_logic
    * google "linear temporal logic functional reactive programming"
    * https://www.seas.harvard.edu/sites/default/files/files/archived/Czaplicki.pdf
    * https://dl.acm.org/citation.cfm?doid=3828.3837
* [LTL FRP talk](https://www.slideshare.net/SergeiWinitzki/temporal-logic-and-functional-reactive-programming) references
    * [Krishnaswamy's paper](https://people.mpi-sws.org/~neelk/simple-frp.pdf)
        * References 5,17,39,27
* https://dtai.cs.kuleuven.be/problog/ (I like the idea of overloading operators to work against variables representing distributions)
* Combinatory logic https://en.wikipedia.org/wiki/Combinatory_logic
* Graphical linear algebra
* Process algebra (and statecharts and bigraphs...)
* Polymorphism (parametric, and other kinds) - I want to see some usage of polymorphism as the foundation of load-balancing and being able to switch out impls (where in this case impls are real automatons running live).

## Roger's Notes

* Monitoring
* Availability (mostly read)
* Utility Rate

## Price based scheduling

Appears to be slides for a talk, and are hard to read on their own.

## Other

* https://landing.google.com/sre/book/index.html
* [Dominant Resource Fairness](https://people.eecs.berkeley.edu/~alig/papers/drf.pdf)
* (read) [Quasar](http://www.industry-academia.org/download/2014-asplos-quasar-Stanford-paper.pdf)
    * [papers that cite it](https://scholar.google.com.au/scholar?gws_rd=cr&dcr=0&um=1&ie=UTF-8&lr&cites=9277981620153489554)
    * [author](http://www.csl.cornell.edu/~delimitrou/)
    * Roger's notes
    * (started reading) [Reference 20: Paragon](http://csl.stanford.edu/~christos/publications/2013.paragon.asplos.pdf)
    * (read) [Reference 18: QoS-Aware Admission Control](https://www.usenix.org/system/files/conference/icac13/icac13_delimitrou.pdf)
        * [Reference 27: Omega](https://static.googleusercontent.com/media/research.google.com/en//pubs/archive/41684.pdf)
    * (read) [Reference 45: Q-Clouds](https://www.microsoft.com/en-us/research/wp-content/uploads/2010/04/QClouds.pdf)
    * (read) [Reference 69: Bubble-flux](http://clarity-lab.org/wp-content/papercite-data/pdf/yang13isca.pdf)
* http://www.perfdynamics.com/Manifesto/USLscalability.html
* https://scholar.google.com.au/scholar?as_ylo=2017&q=IC-scheduling+theory&hl=en&as_sdt=0,5
* Worlds of Events references
    * [Reference 4: Causality, Knowledge and Coordination](https://arxiv.org/pdf/1112.4428.pdf)
* https://en.wikipedia.org/wiki/Flight_envelope
* SBDO / Dynamic Constraint Optimisation
    * (read) [Summary](https://www.dropbox.com/s/1rcey7s3rho13or/59250641.pdf?dl=0)
    * (read) [Draft](https://www.dropbox.com/s/umuyepakpdb111g/article.pdf?dl=0)
    * (read) [SBSD](http://ro.uow.edu.au/cgi/viewcontent.cgi?article=1147&context=infopapers)
* http://www.prismmodelchecker.org/

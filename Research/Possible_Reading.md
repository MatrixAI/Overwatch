# Future Reading

## Monitoring Tools

### Unread

* https://www.netronome.com/blog/bpf-ebpf-xdp-and-bpfilter-what-are-these-things-and-what-do-they-mean-enterprise/

### Read Later

* http://misfra.me/state-of-the-state-part-iii
* https://news.ycombinator.com/item?id=16592303
* http://fractio.nl/2014/02/12/data-driven-alerting-with-flapjack-puppet-hiera/
* http://jasonwilder.com/blog/2012/01/03/centralized-logging/
* http://jasonwilder.com/blog/2013/07/16/centralized-logging-architecture/
* http://en.wikipedia.org/wiki/Profiling_%28computer_programming%29
* http://www.brendangregg.com/blog/2015-07-08/choosing-a-linux-tracer.html
* https://news.ycombinator.com/item?id=8450147 (looks of good opinions here!) (about alerts, not monitoring)
* https://qmonnet.github.io/whirl-offload/2016/09/01/dive-into-bpf/
* https://github.com/google/stenographer - this looks really useful for capturing lots of packets

## Monitoring Theory

### Unread

* http://www.diku.dk/OLD/undervisning/2005v/347/p121-joyce.pdf
* http://ieeexplore.ieee.org/xpl/login.jsp?tp=&arnumber=1703189&url=http%3A%2F%2Fieeexplore.ieee.org%2Fiel5%2F11167%2F35938%2F01703189.pdf%3Farnumber%3D1703189
* http://ieeexplore.ieee.org/xpl/login.jsp?tp=&arnumber=5984319&url=http%3A%2F%2Fieeexplore.ieee.org%2Fxpls%2Fabs_all.jsp%3Farnumber%3D5984319
* http://arxiv.org/ftp/arxiv/papers/1204/1204.0179.pdf
* http://en.wikipedia.org/wiki/Distributed_control_system
* http://en.wikipedia.org/wiki/Teletraffic_engineering
* Bernoulli Sampling
* https://github.com/umbrant/QuantileEstimation
    * (skimmed) [Cormode, Korn, Muthukrishnan, and Srivastava "Effective Computation of Biased Quantiles over Data Streams" in ICDE 2005](https://www.cs.rutgers.edu/~muthu/bquant.pdf)
    * [Greenwald and Khanna, "Space-efficient online computation of quantile summaries" in SIGMOD 2001](http://www.cs.dartmouth.edu/~ac/Teach/CS49-Fall11/Papers/greenwald-quantiles.pdf)
* http://marios.io/2010/03/02/stream-algorithms-order-statistics/
* http://nuit-blanche.blogspot.com.au/2014/01/frugal-streaming-and-sparse-recovery.html?m=1
* https://en.wikipedia.org/wiki/Unevenly_spaced_time_series

### Read Later

* OpenTracing specification
* http://www.lsv.ens-cachan.fr/Publis/PAPERS/PDF/AMB-icde08.pdf
* http://www.nt.ntnu.no/users/skoge/prost/proceedings/adchem09/cd/abstract/78.pdf
* http://digitalcommons.calpoly.edu/cgi/viewcontent.cgi?article=1013&context=csse_fac

## Language Semantics

* https://github.com/pfq/PFQ
* https://en.wikipedia.org/wiki/Constraint_logic_programming
* (read) https://en.wikipedia.org/wiki/Linear_temporal_logic
    * google "linear temporal logic functional reactive programming"
    * (read) [Elm Paper](https://www.seas.harvard.edu/sites/default/files/files/archived/Czaplicki.pdf)
        * (skimmed) [Reference 28: Arrowised FRP](http://haskell.cs.yale.edu/wp-content/uploads/2011/02/workshop-02.pdf)
    * https://dl.acm.org/citation.cfm?doid=3828.3837
* [LTL FRP talk](https://www.slideshare.net/SergeiWinitzki/temporal-logic-and-functional-reactive-programming) references
    * (mostly read) [Krishnaswamy's paper](https://people.mpi-sws.org/~neelk/simple-frp.pdf)
        * References 5,7,39,27 (hard to find)
* https://dtai.cs.kuleuven.be/problog/ (I like the idea of overloading operators to work against variables representing distributions)
    * (started) https://lirias.kuleuven.be/bitstream/123456789/392821/3/plp2cnf.pdf
        * Other PLP languages, including ICL, PRISM, and LPAD/CP-logic.
    * (read) https://lirias.kuleuven.be/bitstream/123456789/146072/1/ijca
* Combinatory logic https://en.wikipedia.org/wiki/Combinatory_logic
* Graphical linear algebra
* Process algebra (and statecharts and bigraphs...)
* https://github.com/hakaru-dev/hakaru

## Other

* (started) https://landing.google.com/sre/book/index.html
* (started) [Dominant Resource Fairness](https://people.eecs.berkeley.edu/~alig/papers/drf.pdf)
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
* http://www.prismmodelchecker.org/
    * (skimmed) [PRISM Paper (2008a)](https://link.springer.com/chapter/10.1007/978-3-540-78652-8_5)
    * (skimmed) [PRISM Paper (2008b)](https://link.springer.com/article/10.1007%2Fs10844-008-0062-7)
* https://github.com/aws/aws-cli/blob/develop/awscli/topics/s3-config.rst
* ring buffer disruptor pattern
* tsung
* https://www.kernel.org/doc/Documentation/networking/filter.txt
* https://github.com/iovisor/bcc/blob/master/src/python/bcc/__init__.py line 1136

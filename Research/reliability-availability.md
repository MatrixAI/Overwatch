# \[WIP\] Reliability and Availability
## [ Basics](http://www.eventhelix.com/RealtimeMantra/FaultHandling/reliability_availability_basics.htm#.W4n2zBRfiHt)

### Reliability parameters
- Mean Time Between Failures (MTBF)  
  - average time between failure of hardware modules.
  - defect rate times KLOCs executed per second

- Mean Time to Failure (MTTF)

- FITS  
The total number of failures of the module in a billion hours.
- Mean Time To Repair (MTTR)  
The time taken to
  - repair a failed hardware module.
  - reboot after a software fault is detected.

### Availability
The percentage of time when system is operational.  
`A = MTBF/(MTBF + MTTR)`

#### Availability in Series
A system is operational only if part x and part y are both available:  
`A = AxAy`

#### Availability in Parallel
A system is operational if either of the 2 part x's are available:  
`A = 1 - (1 - Ax)^2`

#### Partial Operation Availability
A system is considered operational if M out of N parallel components are available:  
`A(N,M) = sum(N!/(i! * (N - i)!) * A^(N - i) * (1 - A)^i) for i from 0 to M`
![partial operation availability equation](http://www.eventhelix.com/RealtimeMantra/FaultHandling/images/partial-availability.gif)

## Quantile Estimation and Reliability
### Quantile [wikipedia](https://en.wikipedia.org/wiki/Quantile)
Quantiles are cut points dividing the range of a probability distribution into contiguous intervals with equal probabilities
- There is one less quantile than the number of groups created.
- Median is the only 2-quantile

The k-th q-quantile is the data value where the cumulative distribution function crosses k/q. That is, x is a k-th q-quantile for a variable X if
- Pr[X < x] ≤ k/q or, equivalently, Pr[X ≥ x] ≥ 1 − k/q, and
- Pr[X ≤ x] ≥ k/q or, equivalently, Pr[X > x] ≤ 1 − k/q.

### [Quantile Function](https://en.wikipedia.org/wiki/Quantile_function)
- The inverse of cumulative distribution function
- Given a probability p, returns a threshold x where p percent of values in the distribution will fall below or equal to x.
- Q(p) = inf {x &in; R : p &le; F(x)}
- If continuous, Q = F^-1

### Survival Analysis
#### [Basics](https://en.wikipedia.org/wiki/Survival_analysis)
- **Survival(or Reliability) Function**: the probability that time of death `T` (random variable) is later than some specific time `t`,
  - S(t) = Pr(T > t)
  - Survival Function is non-increasing.
- **Life distribution function**: complement of Survival Function, the probability of time of death `T` is earlier than or equal to some specific time `t`,
  - F(t) = Pr(T &le; t) = 1 - S(t)
- **Density function** of the lifetime distribution or **Event density**: derivative of `F(t)`
  - f(t) = F'(t) = dF(t) / dt
  - rate of death or failure per unit time, probability of death at time `t`
- **Future lifetime** at a given time `t0` is the time till death, T - t0d

#### Hazard rate function
- The probability of failure in the next small interval of time after x, given no failure has occured ini (0, x].  
  h(x) = lim_&delta;&rightarrow;0(P{x &le; X &le; x + &delta; | X > x} / &delta;)  

- if F(x) is continuous,   
  h(x) = f(x) / F&#x0304;(x) = - (d log F&#x0304;(x)) / dx

#### Mean residue function

#### Variance residue function

#### Percentile residue function

### Quantile-Based Reliability Concepts
The primary concern in reliability theory is to understand the patterns in which failures occur, for different mechanisms and under varying operating environments, as a function of age.


## For Overwatch
### Scope of availability and reliability
Monitors simple QoS metrics at automaton level and aggregate them into complex metrics at service level.
- Look into machine learning descriptors for aggregation and complex metrics.
- Look into control system engineering for lower level reactively controlled metrics.

### Definition of failure
The definition of failure, or a system being not available, could be based on performance.

#### Latency
- when latency goes above certain threshold, a service can be declared unavailable. This is a binary choice, suitable for things like real time systems with hard requirements, but not necessarily for matrix.  

- Quantile estimation is useful in that instead of a true/false answer, it measure QoS on a more generally on a flexible scale. It is more suitable for services Matrix is targeting. This also relates to a partial operation availability model.
  - Look into Service-Level Agreement and Site Reliability Engineering (google book chapters 4,6,17,22,etc) for practical considerations of services.

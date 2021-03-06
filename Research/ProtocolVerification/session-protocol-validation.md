# [A Framework for Validating Session Protocols](http://spw17.langsec.org/papers/tse-validating-session-protocols.pdf)

## Scope/Objective
Given a graphical/textual representation of a protocol state machine, create session
parsers: parsers that ensure a sequence of well-formed
protocol messages follows the rules laid out by the protocol.

## Outcome
Embedded DSL for describing the protocol state machine, system for passing sequences of messages throught the state machine and routines to generate a graphical representation of the state machine.

### Embedded DSL
An embedded DSL is one that builds its constructs upon an existing language

### eDSL Structure
#### State
connection status and more such as host info or custom data structures

#### Transitions
Transition contains a name, a list of tests and a list of effects.
```haskell
type Transition = (String, [Test], [Effect])

data Test = Test {
    name :: String
  , runTest :: (State, Message) -> Bool
}

data Effect = Effect {
    name :: String
  , runEffect :: State -> State -> Message -> State
}  
```
DFA contains a list of possible transitions starting from a connection status.
```haskell
type DFA = [(ProtocolStatus, [Transition])]
```

### Graph Gen
Generated by parsing the eDSL code. Useful for visual/manual comparision of implementation and specification.

## Followup/future Reading
Peter C. Johnson. Towards A Verified Complex Protocol
Stack in a Production Kernel: Methodology and
Demonstration. Tech. rep. TR2016-803. Hanover, NH:
Dartmouth College, Computer Science, 2016.

Other efforts include Pack-etTypes [8], intended for ad-hoc data formats; GAPA [2], intended mostly for application-level protocols; and, more recently, Nail [1].

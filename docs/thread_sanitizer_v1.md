# Internals

- `Tid` (Thread ID): a unique number identifying a thread of
the running program
- `ID`: a unique ID of a memory location
- `EventType`: one of Read, Write, WrLock, RdLock, WrUnlock, RdUnlock, Signal, Wait
- `Event`: a triplet ${EventType`, `Tid`, `ID`}$
- `Lock`: An ID that appeared in a locking event
    - A lock $L$ is `write-held` by a thread $T$ at a given  point of time if the number of events $W_r Lock_T (L)$ observed so far is greater than the number of events $W_rUnlock_T (L)$
    - A lock $L$ is `read-held` by a thread $T$ if it is write-held by $T$ or if the number of events $R_DLock_T (L)$ is greater than the number of events $R_D Unlock_T (L)$.
- `Lock Set (LS)`: A set of locks
- `Writer Lock Set` ($LS_{Wr}$): The set of all write-held locks of a given thread
- `Reader Lock Set` ($LS_{RD}$): The set of all read-held locks of a given thread
- `Event Lock Set`: The informatino that allows the user to understand where the given event has appeared (usually a stack trace)
- `Segment`: A squence of events of one thread that contains only memory access events (ie.e no synchronization events)
- `Happens-before arc`: A pair of events $X = SIGNAL_{T_X}(A_X)$ and $Y = WAIT{T_X}(A_Y)$ such that $A_X = A_Y$, $T_X \neq T_Y$ and $X$ is observed first.
- `Happens-before` partial ordering relation $\preccurlyeq$: Given two events $X = Type X_{T_X}(A_X)$ and $Y = TYPE Y_{T_Y}(A_Y)$, the event $X$ `happens-before` the event $Y$ ($X \preccurlyeq Y$) if $X$ has been observed before $Y$ and at least on of the following statements is true:
    - $T_X = T_Y$
    - $\{X,Y\}$ is a happens-before arc
    - $\exists E_1, E_2: X \preccurlyeq E_1 \preccurlyeq E_2 \preccurlyeq Y$
- `Segment Set`: A set of $N$ segments $\{S_1, S_2, ..., S_N\}$ such that $\forall i,j: S_i \preccurlyeq S_j$
- `Concurrent`: Two memory access events $X$ and $Y$ are concurrent if $X !\preccurlyeq Y$ and $Y !\preccurlyeq X$ and the intersection of the lock sets of these events is empty
- `Data Race`: a data race is a situation when two threads concurrently access a shared memory location (i.e. there are two concurrent memory access events) and at least one of the accesses is a $WRITE$.

- `Global State`:  Information about the synchronization events that have been observed so far (lock sets, happens-before arcs)
- `Shadow Memory` (per-ID state): Information about each memory location of the running program
    - `writer segment set` $SS_{Wr}$: Set of segments where the writes to the ID appeared ($\forall S_w \in SS_{Wr}$)
    - `reader segment set` $SS_{Rd}$: Set of segments where the reads from the ID appeared ($\forall S_r \in SS_{Rd}$)
    - where all segments in $SS_{Rd}$ happen-after or are unrelated to segments in $SS_{Wr}$: $S_r !\preccurlyeq S_w$


## Functions

```
handleReadOrWriteEvent(isWrite: bool, Tid: Tid, ID) {
    if (isWrite)
        handleWrite(WRITE(T_id))
    else
        handleRead(READ(T_id))

    SS_Wr = 
}
```

## Handle Read or Write Event

### Arguments
- isWrite: Indicates whether or not the event is a write event
- Tid: The ID of the thread this event occured on
- ID: The ID of the memory location this event accessed

### Case 1: Read event



### Case 2: Write event
1. Set the reader segment set $SS_{Rd}$ of the memory location to the set of read operations already in the set that did not happen before the current segment
2. Set the writer segment set $SS_{Wr}$ of the memory location to the union of
- the set of read operations already in the set that did not happen before the current segment and 
- the events in the current segment
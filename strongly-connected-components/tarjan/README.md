# Tarjan's algorithm implementation in C++

- Performs only one complete traversals of the graph
- If the graph is represented as an adjacency list, then the algorithm runs in Theta(|V|+|E|) time (linear)
- If the graph is represented as an adjacency matrix, then the algorithm runs in Big-O(|V|^2) time
- The Tarjan's algorithm runs faster than the Kosaraju-Sharir algorithm.

![Graph](_images/graph.png)

## Pseudocode

```
input: graph G = (V, E)
output: set of strongly connected components

// every node has following fields:
// index: a unique number to ID node
// lowlink: ties node to others in SCC
// pred: pointer to stack predecessor
// instack: true if node is in stack

procedure push( v )
  // stack may be null
  v.pred = S;
  v.instack = true;
  S = v;
end push;

function pop( v )
  // val param v is stack copy
  S = v.pred;
  v.pred = null;
  v.instack = false;
  return v;
end pop;

procedure find_scc( v )
  v.index = v.lowlink = ++index;
  push( v );
  foreach node w in succ( v ) do
    if w.index = 0 then // not yet visited
      find_scc( w );
      v.lowlink = min( v.lowlink, w.lowlink );
    elsif w.instack then
      v.lowlink = min( v.lowlink, w.index );
    end if
  end foreach

  if v.lowlink = v.index then // v: head of SCC
    SCC++ // track how many SCCs found
    repeat
      x = pop( S );
      add x to current strongly connected component;
    until x = v;
    output the current strongly connected component;
  end if
end find_scc;

index = 0;  // unique node number > 0
S = null;   // pointer to node stack
SCC = 0;    // number of SCCs in G
foreach node v in V do
  if v.index = 0 then // yet unvisited
    find_scc( v );
  end if
end foreach;
```

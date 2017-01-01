# Kruskal's algorithm implementation in C++

- Kruskal’s algorithm stops after |E(G)| iterations and returns a minimum spanning tree (however, we need to sort the edges first)

![Graph](_images/graph.png)

## Pseudocode

```
input: A graph G with a weight function w : E(G) -> Real Numbers 

Sort all edges e1,..., em (where m = |E(G)|) from E(G) so that w(e1) <=  ... <= w(em).
K :=  (V(G),∅)
for i:=1 to m {
  if K + edge {u,v} is an acyclic grapth, then
    K := K + edge {u,v}	
}

output: a minimum spanning tree K
```

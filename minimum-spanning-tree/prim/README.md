# Prim's algorithm implementation in C++

- In every iteration just one vertex is added to K, so the loop must stop after |V G | iteration in maximum.
- The result graph K is a tree because only a leaf is always added to the tree. Furthermore, K has |V G | vertices – it is a spanning tree.
- 

![Graph](_images/graph.png)

## Pseudocode

```
input: graph G with a weight function w: E(G) -> Real Numbers

Select an arbitrary vertex v0 ∈ V(G)
K := ({v0,∅})
while (|V(K)| != |V(G)|) {
  Select edge {u,v} ∈ E(G)
  where u ∈ V(K) and v ∉ V(K) so that
    w({u,v}) is minimum
  K := K + edge {u,v}
} 

output: minimum spanning tree K
```

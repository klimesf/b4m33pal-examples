# Breadth First Search algorithm implementation in C++

- Time complexity is O(|V|+|E|) for adjacency list and O(|V^2|) for adjacency matrix

## Pseudocode

```
procedure bfs(start_vertex : Vertex)
var to_visit : Queue = empty;
    visited : Vertices = empty; {
  to_visit.push(start_vertex);
  while (size(to_visit) != 0) {
    v = to_visit.pop();
    if v not in visited then {
      visited.add(v);
      for all x in neighbors of v {
        to_visit.push(x);
      }
    }
  } 
}
```


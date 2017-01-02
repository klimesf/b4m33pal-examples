# Sieve of eratosthenes implementation in C++

- Time complexity: O(n log log n)

## Pseudocode

```
EratosthenesSieve (n)
  Let A be an array of Boolean values, indexed by integers 2 to n, initially all set to true
  for i=2 to sqrt(n)
    if A[i] = true then
      for j = i^2, i^2+i, i^2+2i, i^2+3i, ..., not exceeding n
        A[i] := false
  end
  output all i such that A[i] is true
end
```

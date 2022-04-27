# GraphRanker

Final project of the `Algorithm and Principles of Computer Science` course (Politecnico di Milano)
The objective of the project is to write a program in **C** that manages the ranking of weighted graphs. 
The ranking keeps track of the "best" `k` graphs. The program
receives (located in the first line of the input file) two parameters that represent the number of nodes of the graphs `d` and the length of the ranking `k`,
followed by a sequence of commands between:

- `AddGraph [adjacency matrix]`
- `TopK`

`d`and `k` are representable with 32-bit integers.

## Comamands

### AddGraph

`AddGraph`  requires to add a graph to those considered in the ranking di aggiungere un grafo a quelli considerati per stilare
la classifica. The command is followed by adjacency matrix, printed row by row, with the elements seprated with commas.
The weights of the arcs of the element graph are integers in the interval `[0; 2^32 – 1]`.

Example of usage:

```txt
AddGraph
3,7,42
0,7,2
7,4,3
```

### TopK

`TopK` considers each graph from the beginning of the program until this command. The command requires that the program prints the index of the `k` graphs that have the `k` minimum value for the sum of minimum paths starting from node 0 to the other nodes. If there are nodes with same value, the program should give more relevance to the graph that entered in the rank before. The distances that aren't reachable from node 0 are considered null. The `k` indexes are printed in one line separated by a space, in any order.

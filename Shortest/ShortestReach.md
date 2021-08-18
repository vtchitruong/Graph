Determine the shortest distances from the start node to the others, using BFS.  
The distance between any 2 nodes is always 6.  
If a node is isolated, its distance should be -1.  
Return the list in node number ascending order.

### Constraints
2 <= n <= 1000 (node)
1 <= m <= n(n - 1) / 2 (edge)
1 <= u, v, start <= n

### Sample Input
4 2  
1 2  
1 3  
1   

### Sample Output
6 6 -1    

### Explanation
The shortest distances from start = 1 to the other nodes are one edge to node 2, one edge to node 3, and there is no connection to node 4. 

### Source
The problem can be found at [HackerRank](https://www.hackerrank.com/challenges/ctci-bfs-shortest-reach/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=graphs).

Find the nearest path connecting any two nodes of the same color.  
Each edge has a weight of 1.  
Return -1 if not found.  

### Constraints
1 <= node <= 10^6  
1 <= edge <= 10^6  
1 <= color[i] <= 10^8  

### Sample Input
4 3  
1 2  
1 3  
4 2  
1 2 1 1  
1  

### Sample Output
1  

### Explanation
4 nodes  
3 edges  
color = {1 2 1 1} for each node.  
The last line is the color to analyze, which is 1.  
The nearest path is 1.  

### Source
The problem can be foune at [HackerRank](https://www.hackerrank.com/challenges/find-the-nearest-clone/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=graphs).
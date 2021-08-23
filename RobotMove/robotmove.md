Find a path for the robot to get out of the maze.  
The maze is denoted by a 1-based index grid.  
The robot knows the positions of starting and finishing.  
It can move into the position of 0, but not the position of 1.  

### Constraints
2 <= row, col <= 1000  

### Sample Input
4 7 3 4 2 6  
1000000  
0010100  
0000000  
1101000  

### Sample Output
3 4  
3 5  
3 6  
2 6  

### Explanation
The maze has row of 4 and column of 7, which is 1-based indexing.  
The start position is [3,4] and the finish position is [2,6].  
Each cell of the output path is listed line by line.  
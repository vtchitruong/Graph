Guide the explorer out of the forest.  
There is only 1 path from his position to the edge of the forest.  
E is the position of the explorer.  
He can go into the position of O, but not the position of X.  

### Constraints
2 <= row, col <= 1000  

### Sample Input
5 5  
XXXXX  
XEOOX  
XXXOX  
XOOOX  
XOXXX  

### Sample Output
1 1  
1 2  
1 3  
2 3  
3 3  
3 2  
3 1  
4 1  

### Explanation
The forest has row of 5 and column of 5.  
The output path is listed from his postion (1,1) to the edge, which is (4,1).  
<br/>
|   | 0 | 1 | 2 | 3 | 4 |
|---|:-:|:-:|:-:|:-:|:-:|
| **0** | X | X | X | X | X |
| **1** | X | E | O | O | X |
| **2** | X | X | X | O | X |
| **3** | X | O | O | O | X |
| **4** | X | O | X | X | X |
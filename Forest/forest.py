import os
import sys
from collections import deque

input_file = os.path.join(sys.path[0], 'forest.inp')
output_file = os.path.join(sys.path[0], 'forest.out')

MAX = 1000
#-----------------------------------------------------------------------------
def input_data():  
    with open(input_file) as f:        
        global rows, cols
        rows, cols = list(map(int, f.readline().split()))

        # read the remnaining lines for the forest
        lines = f.readlines()
        global forest
        forest = list()
        # for line in lines:
        #     forest.append([c for c in line])
        for line in lines:
            forest.append(line)

#-----------------------------------------------------------------------------
def init():
    # locate the start position of the explorer    
    global start
    for row_idx, row_data in enumerate(forest):
        if 'E' in row_data:
            col_idx = row_data.index('E')
            start = [row_idx, col_idx]
            break
    
    # 4 types of steps: up, down, left, right
    global steps
    steps = [(-1, 0), (1, 0), (0, -1), (0, 1)]

    # for output tracing
    global trace
    trace = [[-1 for col in range(cols)] for row in range(rows)] # -1 means not yet visited
 
#-----------------------------------------------------------------------------
def dfs(current):  
    # the explorer reaches the forest boundaries
    if current[0] == 0 or current[0] == rows - 1 or current[1] == 0 or current[1] == cols - 1:
        global finish
        finish = current # the finish position at the boundaries
        return

    global MAX    

    # try each step for next move
    for s in steps:
        next = [current[0] + s[0], current[1] + s[1]]

        if 0 <= next[0] < rows and 0 <= next[1] < cols: # he's still in bound
            if forest[next[0]][next[1]] == 'O': # no trap
                if trace[next[0]][next[1]] == -1: # not yet visited
                    trace[next[0]][next[1]] = current[1] * MAX + current[0]                                        
                    dfs(next)

#-----------------------------------------------------------------------------
def output():
    path = list()
    global finish
    path.append(finish)
    
    while not trace[finish[0]][finish[1]] == -1:
        r = trace[finish[0]][finish[1]] % MAX
        c = trace[finish[0]][finish[1]] // MAX
        path.append([r, c])
        finish = [r, c]

    with open(output_file, 'w') as f:
        result = '\n'.join([str(' '.join([str(number) for number in position])) for position in reversed(path)])    
        f.write(result)

#-----------------------------------------------------------------------------
if __name__ == '__main__':
    input_data()
    init()
    
    global finish    
    dfs(start)
    output()
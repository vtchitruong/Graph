import os
import sys
from collections import deque

input_file = os.path.join(sys.path[0], 'forest.inp')
output_file = os.path.join(sys.path[0], 'forest.out')

MAX = 1000
#-----------------------------------------------------------------------------
def input_data():  
    with open(input_file) as f:        
        global total_rows, total_cols
        total_rows, total_cols = list(map(int, f.readline().split()))

        # read the remnaining lines for the graph
        lines = f.readlines()
        global g # graph
        g = list()
        for line in lines:
            g.append([c for c in line])

#-----------------------------------------------------------------------------
def init():
    # locate the start position of the explorer    
    global start
    for row_idx, row_data in enumerate(g):
        if 'E' in row_data:
            col_idx = row_data.index('E')
            start = [row_idx, col_idx]
            break

    # 4 types of steps
    global steps
    steps = [(-1, 0), (1, 0), (0, -1), (0, 1)] # step up, down, left, right

    global trace # for output tracing
    trace = [[-1 for col in range(total_cols)] for row in range(total_rows)] # -1 means not yet visited
 
#-----------------------------------------------------------------------------
def dfs(current):  
    # the explorer reaches the forest boundaries
    if (current[0] == 0 or current[0] == total_rows - 1 or current[1] == 0 or current[1] == total_cols - 1):
        global finish
        finish = current # the finish position at the boundaries
        return

    global MAX    

    # try each step for next move
    for s in steps:
        next = [current[0] + s[0], current[1] + s[1]]
        if 0 <= next[0] < total_rows and 0 <= next[1] < total_cols: # he's still in bound
            if g[next[0]][next[1]] == 'O': # he can move to the next position
                if trace[next[0]][next[1]] == -1: # the next position is not yet visited
                    trace[next[0]][next[1]] = (MAX + current[1]) * MAX + current[0]
                    
                    current = next # current = next.copy()                    
                    dfs(current) # recursion

#-----------------------------------------------------------------------------
def output():
    p = list() # path
    global finish
    p.append(finish)
    
    while not trace[finish[0]][finish[1]] == -1:
        r = int(trace[finish[0]][finish[1]] % MAX)
        c = int(trace[finish[0]][finish[1]] / MAX - MAX)
        p.append([r, c])
        finish = [r, c]

    with open(output_file, 'w') as f:
        result = '\n'.join([str(' '.join([str(number) for number in position])) for position in reversed(p)])    
        f.write(result)

#-----------------------------------------------------------------------------
if __name__ == '__main__':
    input_data()
    init()
    
    global finish    
    dfs(start)
    output()
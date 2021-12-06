import os
import sys
from collections import deque

input_file = os.path.join(sys.path[0], 'robotmove.inp')
output_file = os.path.join(sys.path[0], 'robotmove.out')

#-----------------------------------------------------------------------------
def input():
    with open(input_file) as f:
        global total_rows, total_cols, start, finish        

        # first line in input file
        total_rows, total_cols, s_x, s_y, f_x, f_y = map(int, f.readline().split())
        start = [s_x, s_y]
        finish = [f_x, f_y]

        # read the remnaining lines for the graph
        lines = f.readlines()
        global g # graph
        g = list()
        g.append([]) # line 0
        for line in lines:                        
            tmp = [c for c in line]
            tmp.insert(0, '0') # for column 0
            g.append(tmp)

#-----------------------------------------------------------------------------
def init():
    global trace
    trace = [['N' for col in range(total_cols + 1)] for row in range(total_rows + 1)] # N: not visited
    trace[start[0]][start[1]] = 'S'

#-----------------------------------------------------------------------------
def spread():
    q = deque()
    q.append(start)

    while q:
        current = q[0]

        # return if the robot reaches the finish cell
        if current == finish:
            return

        # try 4 directions in turn
        if current[0] > 1: # if robot could go up
            if trace[current[0] - 1][current[1]] == 'N':
                if g[current[0] - 1][current[1]] == '0':
                    next = current.copy()
                    next[0] -= 1
                    q.append(next)
                    trace[next[0]][next[1]] = 'U'

        if current[0] < total_rows: # if robot could go down
            if trace[current[0] + 1][current[1]] == 'N':
                if g[current[0] + 1][current[1]] == '0':
                    next = current.copy()
                    next[0] += 1
                    q.append(next)
                    trace[next[0]][next[1]] = 'D'

        if current[1] > 1: # if robot could go left
            if trace[current[0]][current[1] - 1] == 'N':
                if g[current[0]][current[1] - 1] == '0':
                    next = current.copy()
                    next[1] -= 1
                    q.append(next)
                    trace[next[0]][next[1]] = 'L'

        if current[1] < total_cols: # if robot could go right
            if trace[current[0]][current[1] + 1] == 'N':
                if g[current[0]][current[1] + 1] == '0':
                    next = current.copy()
                    next[1] += 1
                    q.append(next)
                    trace[next[0]][next[1]] = 'R'
        
        q.popleft() # remove current

#-----------------------------------------------------------------------------
def output():   
    p = list() # path
    if trace[finish[0]][finish[1]] == 'N': # no path found
        p.append([-1, -1])
    else:        
        while not start == finish:
            tmp = finish.copy()
            p.append(tmp)
            t = trace[finish[0]][finish[1]]
            if t == 'U':
                finish[0] += 1                
            elif t == 'D':
                finish[0] -= 1
            elif t == 'L':
                finish[1] += 1
            elif t == 'R':
                finish[1] -= 1            
        
        p.append(start)
    
    with open(output_file, 'w') as f:        
        for i, cell in enumerate(reversed(p)):
            line = f'{cell[0]} {cell[1]}'
            f.write(line) if i == len(p) - 1 else f.write(line + '\n')                   

#-----------------------------------------------------------------------------
if __name__ == '__main__':    
    input()    
    init()
    spread()
    output()
import os
import sys
from collections import deque

input_file = os.path.join(sys.path[0], 'robotmove2.inp')
output_file = os.path.join(sys.path[0], 'robotmove2.out')

#-----------------------------------------------------------------------------
def input():
    with open(input_file) as f:
        global rows, cols, start, finish        

        # first line in input file
        rows, cols, s_row, s_col, f_row, f_col = map(int, f.readline().split())
        start = [s_row, s_col]
        finish = [f_row, f_col]

        # read the remnaining lines for the maze
        lines = f.readlines()
        global maze
        maze = list()
        maze.append([]) # for line 0
        for line in lines:                        
            tmp = [int(c) for c in line if c != '\n' ]
            tmp.insert(0, 0) # for column 0
            maze.append(tmp)

#-----------------------------------------------------------------------------
def init():
    global trace
    trace = [['N' for col in range(cols + 1)] for row in range(rows + 1)] # N: not visited
    trace[start[0]][start[1]] = 'S'

#-----------------------------------------------------------------------------
def bfs():
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
                if maze[current[0] - 1][current[1]] == 0:
                    next = current.copy()
                    next[0] -= 1
                    q.append(next)
                    trace[next[0]][next[1]] = 'U'

        if current[0] < rows: # if robot could go down
            if trace[current[0] + 1][current[1]] == 'N':
                if maze[current[0] + 1][current[1]] == 0:
                    next = current.copy()
                    next[0] += 1
                    q.append(next)
                    trace[next[0]][next[1]] = 'D'

        if current[1] > 1: # if robot could go left
            if trace[current[0]][current[1] - 1] == 'N':
                if maze[current[0]][current[1] - 1] == 0:
                    next = current.copy()
                    next[1] -= 1
                    q.append(next)
                    trace[next[0]][next[1]] = 'L'

        if current[1] < cols: # if robot could go right
            if trace[current[0]][current[1] + 1] == 'N':
                if maze[current[0]][current[1] + 1] == 0:
                    next = current.copy()
                    next[1] += 1
                    q.append(next)
                    trace[next[0]][next[1]] = 'R'
        
        q.popleft() # remove current

#-----------------------------------------------------------------------------
def output():   
    path = list()

    if trace[finish[0]][finish[1]] != 'N':
        while not trace[finish[0]][finish[1]] == 'S':
            tmp = finish.copy()
            path.append(tmp)
            t = trace[finish[0]][finish[1]]
            if t == 'U':
                finish[0] += 1
            elif t == 'D':
                finish[0] -= 1
            elif t == 'L':
                finish[1] += 1
            elif t == 'R':
                finish[1] -= 1
        
        path.append(start)
    
    with open(output_file, 'w') as f:
        for i in range(len(path) - 1, 0, -1):
            cell = f'{path[i][0]} {path[i][1]}'
            print(cell, file=f)
        
        cell = f'{path[0][0]} {path[0][1]}'
        f.write(cell)

#-----------------------------------------------------------------------------
if __name__ == '__main__':    
    input()    
    init()
    bfs()
    output()
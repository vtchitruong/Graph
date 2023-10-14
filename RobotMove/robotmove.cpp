#include <bits/stdc++.h>

#define inputFile "robotmove2.inp"
#define outputFile "robotmove2.out"

using namespace std;

int rows, cols;
pair<int,int> start, finish; // 1-based index
vector<vector<short>> maze;

vector<vector<char>> trace;

void Input()
{
    ifstream f;
    f.open(inputFile);

    // load data to global variables
    f >> rows >> cols >> start.first >> start.second >> finish.first >> finish.second;
    
    // read each row, then add them to vector g
    string eachRow;
    maze.resize(rows + 1);
    for (int r = 1; r < rows + 1; ++r)
    {
        maze[r].resize(cols + 1);
        
        f >> eachRow;
        for (int c = 1; c < cols + 1; ++c)
        {
            int val = eachRow[c - 1] == '0' ? 0 : 1;
            maze[r][c] = val;
        }        
    }
    
    f.close();
}

void Init()
{
    trace.resize(rows + 1);

    for (int r = 1; r < rows + 1; ++r)
    {
        trace[r].resize(cols + 1, 'N'); // 'N' = not yet visited
    }

    trace[start.first][start.second] = 'S';
}

void Bfs()
{
    queue<pair<int, int>> q;
    q.push(start);
    
    pair<int, int> current; // current cell of the robot
    pair<int, int> next; // temp cell for next move

    while (!q.empty())
    {
        current = q.front();
        
        // return if the robot reaches the finish cell
        if (current == finish)
            return;

        // try 4 directions in turn
        if (current.first > 1) // robot could go up
            if (trace[current.first - 1][current.second] == 'N')
                if (maze[current.first - 1][current.second] == 0)
                {
                    next = current;
                    next.first--;

                    q.push(next);
                    trace[next.first][next.second] = 'U';
                }
        
        if (current.first < rows) // robot could go down
            if (trace[current.first + 1][current.second] == 'N')
                if (maze[current.first + 1][current.second] == 0)
                {
                    next = current;
                    next.first++;

                    q.push(next);
                    trace[next.first][next.second] = 'D';
                }

        if (current.second > 1) // robot could go left
            if (trace[current.first][current.second - 1] == 'N')
                if (maze[current.first][current.second - 1] == 0)
                {
                    next = current;
                    next.second--;

                    q.push(next);
                    trace[next.first][next.second] = 'L';
                }
        
        if (current.second < cols) // robot could go right
            if (trace[current.first][current.second + 1] == 'N')
                if (maze[current.first][current.second + 1] == 0)
                {
                    next = current;
                    next.second++;

                    q.push(next);
                    trace[next.first][next.second] = 'R';
                }

        q.pop();
    }    
}

void Output()
{
    stack<pair<int, int>> path;

    if (trace[finish.first][finish.second] != 'N')
    {
        while (trace[finish.first][finish.second] != 'S')
        {
            path.push(finish);

            switch (trace[finish.first][finish.second])
            {
                case 'U': finish.first++;
                    break;
                case 'D': finish.first--;
                    break;
                case 'L': finish.second++;
                    break;
                case 'R': finish.second--;
                    break;
            }
        }
        path.push(start);
    }

    ofstream f;
    f.open(outputFile);

    if (path.empty())
    {
        f << -1;
    }
    else
    {
        while (path.size() > 1)
        {
            f << path.top().first << ' ' << path.top().second << endl;
            path.pop();
        }
        f << path.top().first << ' ' << path.top().second;
    }

    f.close();
}

int main()
{
    Input();
    Init();  
    Bfs();
    Output();
    
    return 0;
}
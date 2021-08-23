#include <bits/stdc++.h>

#define inputFile "robotmove.inp"
#define outputFile "robotmove.out"

using namespace std;

int totalRow, totalCol;
pair<int,int> start, finish; // 1-based index
vector<vector<int>> g; // graph

vector<vector<char>> trace;

void Input()
{
    ifstream f;
    f.open(inputFile);

    // load data to global variables
    f >> totalRow >> totalCol >> start.first >> start.second >> finish.first >> finish.second;
    
    // read each row, then add them to vector g
    string eachRow;
    g.resize(totalRow + 1);
    for (int r = 1; r < totalRow + 1; ++r)
    {
        g[r].resize(totalCol + 1);
        
        f >> eachRow;
        for (int c = 1; c < totalCol + 1; ++c)
        {
            int val = eachRow[c - 1] == '0' ? 0 : 1;
            g[r][c] = val;
        }        
    }
    
    f.close();
}

void Init()
{
    // trace
    trace.resize(totalRow + 1);
    for (int r = 1; r < totalRow + 1; ++r)
    {
        trace[r].resize(totalCol + 1, 'N'); // 'N' = not yet visited
    }
    trace[start.first][start.second] = 'S';
}

void Spread()
{
    queue<pair<int, int>> q;
    q.push(start);
    
    pair<int, int> current;
    pair<int, int> next;

    while (!q.empty())
    {
        current = q.front();
        
        // return if the robot reaches the finish cell
        if (current == finish)
            return;

        // try 4 directions in turn
        if (current.first > 1) // robot could go up
            if (trace[current.first - 1][current.second] == 'N')
                if (g[current.first - 1][current.second] == 0)
                {
                    next = current;
                    next.first--;

                    q.push(next);
                    trace[next.first][next.second] = 'U';
                }
        
        if (current.first < totalRow) // robot could go down
            if (trace[current.first + 1][current.second] == 'N')
                if (g[current.first + 1][current.second] == 0)
                {
                    next = current;
                    next.first++;

                    q.push(next);
                    trace[next.first][next.second] = 'D';
                }

        if (current.second > 1) // robot could go left
            if (trace[current.first][current.second - 1] == 'N')
                if (g[current.first][current.second - 1] == 0)
                {
                    next = current;
                    next.second--;

                    q.push(next);
                    trace[next.first][next.second] = 'L';
                }
        
        if (current.second < totalCol) // robot could go right
            if (trace[current.first][current.second + 1] == 'N')
                if (g[current.first][current.second + 1] == 0)
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
    stack<pair<int, int>> p; // path

    if (trace[finish.first][finish.second] == 'N')
    {
        p.push({-1, -1});
    }
    else
    {
        while (!(start == finish))
        {
            p.push(finish);

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
        p.push(start);
    }

    ofstream f;
    f.open(outputFile);

    if (p.size() == 1)
    {
        f << p.top().first;
    }
    else
    {
        while (!p.empty())
        {
            f << p.top().first << ' ' << p.top().second;
            if (p.size() > 1) f << endl;

            p.pop();
        }
    }

    f.close();
}

int main()
{
    Input();
    Init();  
    Spread();
    Output();
    
    return 0;
}
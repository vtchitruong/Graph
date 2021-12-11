#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <utility>

#define inputFile "forest.inp"
#define outputFile "forest.out"

using namespace std;

const int MAX = 1000;

int totalRows, totalCols;
vector<string> g; // graph
pair<int, int> start, finish; // the  position of the explorer

vector<vector<int>> trace;
vector<pair<int,int>> steps;

//-----------------------------------------------------------------------------
void Input()
{
    ifstream f;
    f.open(inputFile);

    f >> totalRows >> totalCols;

    // read each row, then add them to vector g
    string eachRow;
    for (int r = 0; r < totalRows; ++r)
    {
        f >> eachRow;
        g.push_back(eachRow);
    }

    f.close();
}

//-----------------------------------------------------------------------------
void Init()
{
    // locate the start position of the explorer
    for (int r = 0; r < totalRows; r++)
    {
        int c = g[r].find('E');

        if (!(c == string::npos))
        {
            start.first = r;
            start.second = c;
            break;
        }
    }

    // 4 types of steps
    steps.push_back({-1, 0}); // up
    steps.push_back({1, 0}); // down
    steps.push_back({0, -1}); // left
    steps.push_back({0, 1}); // right

    // for output tracing
    trace.resize(totalRows);
    for (int r = 0; r < totalRows; ++r)
    {
        trace[r].resize(totalCols, -1); // -1 means not yet visited        
    }
}

//-----------------------------------------------------------------------------
void DFS(pair<int, int> current)
{
    // the explorer reaches the forest boundaries
    if (current.first == 0 || current.first == totalRows - 1 || current.second == 0 || current.second == totalCols - 1)
    {
        finish.first = current.first; // the finish position at the boundaries
        finish.second = current.second;
        return;
    }    

    pair<int, int> next;

    // try each step for next move
    for (int s = 0; s < steps.size(); ++s)
    {
        next.first = current.first + steps[s].first;
        next.second = current.second + steps[s].second;

        if (next.first >= 0 && next.first < totalRows && next.second >= 0 && next.second < totalCols) // he's still in bound
            if (g[next.first][next.second] == 'O') // he can move to the next position
                if (trace[next.first][next.second] == -1) // the next position is not yet visited
                {
                    trace[next.first][next.second] = (MAX + current.second) * MAX + current.first;
                    
                    current.first = next.first;
                    current.second = next.second;
                    DFS(current);
                }
    }
}

//-----------------------------------------------------------------------------
void Output()
{    
    stack<pair<int, int>> p; // path

    p.push(finish); // the explorer is standing at the boundary
    while (!(trace[finish.first][finish.second] == -1))
    {
        int r = trace[finish.first][finish.second] % MAX;
        int c = trace[finish.first][finish.second] / MAX - MAX;

        p.push({r, c});

        finish.first = r;
        finish.second = c;
    }

    ofstream f;
    f.open(outputFile);

    while (!p.empty())
    {
        f << p.top().first << ' ' << p.top().second;
        if (!(p.size() == 1)) f << endl;
        p.pop();
    }  
    
    f.close();
}

//-----------------------------------------------------------------------------
int main()
{
    Input();
    Init();
    DFS(start);
    Output();   

    return 0;
}
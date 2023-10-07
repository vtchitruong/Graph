#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <utility>

#define inputFile "forest.inp"
#define outputFile "forest.out"

using namespace std;

const int MAX = 1000;

int rows, cols;
vector<string> forest;
pair<int, int> start, finish; // the start position and the finish position of the explorer

vector<vector<int>> trace;
vector<pair<int,int>> steps;

//-----------------------------------------------------------------------------
void Input()
{
    ifstream f;
    f.open(inputFile);

    f >> rows >> cols;

    // read each row, then add them to vector forest
    string eachRow;
    for (int r = 0; r < rows; ++r)
    {
        f >> eachRow;
        forest.push_back(eachRow);
    }

    f.close();
}

//-----------------------------------------------------------------------------
void Init()
{
    // locate the start position of the explorer
    for (int r = 0; r < rows; r++)
    {
        int c = forest[r].find('E');

        if (c != string::npos) // if found
        {
            start.first = r;
            start.second = c;
            break;
        }
    }

    // 4 types of steps: up, down, left, right
    steps = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // for output tracing
    trace.resize(rows);
    for (int r = 0; r < rows; ++r)
    {
        trace[r].resize(cols, -1); // -1 means not yet visited        
    }
}

//-----------------------------------------------------------------------------
void Dfs(pair<int, int> current)
{
    // the explorer reaches the forest boundaries
    if (current.first == 0 || current.first == rows - 1 || current.second == 0 || current.second == cols - 1)
    {
        finish.first = current.first; // the finish position at the boundaries
        finish.second = current.second;
        return;
    }    

    pair<int, int> next;

    // try each step for next move
    for (int s = 0; s < 4; ++s)
    {
        next.first = current.first + steps[s].first;
        next.second = current.second + steps[s].second;

        if (next.first >= 0 && next.first < rows && next.second >= 0 && next.second < cols) // he's still in bound
            if (forest[next.first][next.second] == 'O') // no trap
                if (trace[next.first][next.second] == -1) // not yet visited
                {
                    trace[next.first][next.second] = current.second * MAX + current.first;
                    Dfs(next);
                }
    }
}

//-----------------------------------------------------------------------------
void Output()
{    
    stack<pair<int, int>> path; // result path

    path.push(finish); // the explorer is standing at the boundary
    while (trace[finish.first][finish.second] != -1)
    {
        int r = trace[finish.first][finish.second] % MAX;
        int c = trace[finish.first][finish.second] / MAX;

        path.push({r, c});

        finish.first = r;
        finish.second = c;
    }

    ofstream f;
    f.open(outputFile);

    while (!path.empty())
    {
        f << path.top().first << ' ' << path.top().second;
        if (path.size() != 1) f << endl;
        path.pop();
    }  
    
    f.close();
}

//-----------------------------------------------------------------------------
int main()
{
    Input();
    Init();
    Dfs(start);
    Output();   

    return 0;
}
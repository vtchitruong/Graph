#include <bits/stdc++.h>

#define inputFile "maze.inp"
#define outputFile "maze.out"

using namespace std;

const int MAX = 1000;

int totalRow, totalCol;
vector<string> g; // graph
int Er, Ec; // the position of the explorer

vector<vector<int>> trace;
vector<pair<int,int>> step;

void Input()
{
    ifstream f;
    f.open(inputFile);

    f >> totalRow >> totalCol;

    // read each row, then add them to vector g
    string eachRow;
    for (int r = 0; r < totalRow; ++r)
    {
        f >> eachRow;
        g.push_back(eachRow);
    }

    f.close();
}

void Init()
{
    // step
    step.push_back({-1, 0});
    step.push_back({1, 0});
    step.push_back({0, -1});
    step.push_back({0, 1});

    // trace
    trace.resize(totalRow);
    for (int r = 0; r < totalRow; ++r)
    {
        vector<int> tmp(totalCol, -1);
        trace[r] = tmp;
    }

    // locate the explorer
    for (int r = 0; r < totalRow; r++)
    {
        int colFound = g[r].find('E');

        if (!(colFound == string::npos))
        {
            Er = r;
            Ec = colFound;
            break;
        }
    }
}

void dfs(int &currentEr, int &currentEc)
{
    // the explorer reaches the maze outline
    if (currentEr == 0 || currentEr == totalRow - 1 || currentEc == 0 || currentEc == totalCol - 1)
        return;

    int nextEr, nextEc;

    for (int i = 0; i < step.size(); ++i)
    {
        nextEr = currentEr + step[i].first;
        nextEc = currentEc + step[i].second;

        if (nextEr >= 0 && nextEr < totalRow && nextEc >= 0 && nextEc < totalCol)
        {
            if (g[nextEr][nextEc] == 'O') // he can move
            {
                if (trace[nextEr][nextEc] == -1)
                {
                    trace[nextEr][nextEc] = (MAX + currentEc) * MAX + currentEr;
                    
                    currentEr = nextEr;
                    currentEc = nextEc;
                    dfs(currentEr, currentEc);
                }
            }
        }
    }
}

void Output()
{
    int _r;
    int _c; // temporary position

    stack<pair<int, int>> p; // path

    p.push({Er, Ec}); // the explorer is standing at the boundary
    while (!(trace[Er][Ec] == -1))
    {
        _r = trace[Er][Ec] % MAX;
        _c = trace[Er][Ec] / MAX - MAX;

        p.push({_r, _c});

        Er = _r;
        Ec = _c;
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

int main()
{
    Input();
    Init();
    dfs(Er, Ec);    
    Output();

    return 0;
}
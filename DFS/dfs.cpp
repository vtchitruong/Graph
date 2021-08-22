#include <bits/stdc++.h>

#define inputFile "dfs1.inp"
#define outputFile "dfs1.out"

// số đỉnh tối đa
#define MAX 1000

using namespace std;

// global variables: number of vertices/nodes, number of edges, start node, finish node
int vertex, edge, start, finish;

// adjacency matrix
vector<vector<int>> a;

vector<int> trace; // trace[v] = u, preceding of v is u

void Input()
{
    ifstream f;
    f.open(inputFile);

    // global variables
    f >> vertex >> edge >> start >> finish;

    // init adjacent matrix
    a.resize(vertex + 1);

    int u, v;
    
    // read each line in turn, then create and add a vector to a[i]
    for (int i = 1; i < edge + 1; ++i)
    {
        f >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    f.close();
}

void Init()
{
    trace.resize(vertex + 1, 0);
    trace[start] = -1;
}

void dfs(int current) // current node to start
{
    // iterate all adjaccent nodes of node s
    for (vector<int>::iterator i = a[current].begin(); i != a[current].end(); ++i)
    {
        if (!trace[*i]) // not yet visited
        {
            trace[*i] = current;
            dfs(*i);
        }
    }
}

void Output()
{
    stack<int> p; // path result

    if (!trace[finish]) // no preceding of finish node
    {
        p.push(-1);
    }
    else
    {
        // using loop to trace back from finish node to start node
        while (!(start == finish))
        {
            p.push(finish);
            finish = trace[finish];
        }

        p.push(start);
    }

    ofstream f;
    f.open(outputFile);

    if (p.top() == -1)
    {
        f << -1;
    }
    else
    {
        while (!p.empty())
        {
            f << p.top() << ' ';
            p.pop();
        }
    }
    f.close();
}

int main()
{
    Input();
    Init();
    dfs(start);
    Output();

    return 0;
}
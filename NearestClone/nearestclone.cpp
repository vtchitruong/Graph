#include <bits/stdc++.h>

#define inputFile "nc2.inp"
#define outputFile "nc2.out"

using namespace std;

int node;
int edge;
vector<vector<int>> a; // adjacent matrix
vector<int> color;
int c; // color

void Input()
{
    ifstream f;
    f.open(inputFile);

    f >> node >> edge;

    // adjacent matrix
    a.resize(node + 1);

    int u, v;
    for (int i = 0; i < edge; ++i)
    {
        f >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    // color of each node
    color.resize(node + 1);
    int x;
    for (int u = 1; u < node + 1; ++u)
    {
        f >> x;
        color[u] = x;
    }

    f >> c;

    f.close();
}

// using BFS
int Nearest(int s)
{
    int d = 1e9; // distance
    
    vector<bool> visited(node + 1, false);
    
    queue<pair<int, int>> q;
    q.push({s, 0}); // {vertex, distance from start node}
    visited[s] = true;

    pair<int, int> current; // {node, distance from start node}
    while (!q.empty())
    {
        current = q.front();
        for (int v : a[current.first])
        {
            if (!visited[v])
            {
                // return when meeting a node of the same color
                if (color[v] == c)
                {
                    d = current.second + 1;
                    return d;
                }
                
                visited[v] = true;

                // enqueue and add distance
                q.push({v, current.second + 1 });
            }
        }
        q.pop();
    }
    
    return d;
}

void Output()
{
    int min_dist = 1e9;
    int tmp_dist;
    for (int u = 1; u < node + 1; ++u)
    {
        if (color[u] == c)
        {
            tmp_dist = Nearest(u);
            min_dist = min (min_dist, tmp_dist);
        }
    }

    if (min_dist == 1e9) min_dist = -1;

    ofstream f;
    f.open(outputFile);

    f << min_dist;

    f.close();
}


int main()
{
    Input();
    Output();

    return 0;
}
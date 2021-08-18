#include <bits/stdc++.h>

#define inputFile "shortest5.inp"
#define outputFile "shortest5.out"

using namespace std;

int n; // vertex
int m; // edge
int start;
vector<vector<int>> a; // adjacent matrix

void Input()
{
    ifstream f;
    f.open(inputFile);

    f >> n >> m;

    a = vector<vector<int>>(n + 1, vector<int>());
    
    int u, v;
    for (int i = 0; i < m; ++i)
    {
        f >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    f >> start;

    f.close();
}

// using BFS
vector<int> shortest_reach(int s)
{
    queue<int> q;
    q.push(start);

    vector<bool> visited(n + 1, false);
    visited[s] = true;

    vector<int> d(n + 1, 0); // distance from node start to node i

    int current, next;
    while (!q.empty())
    {
        current = q.front();
    
        for (int i = 0; i < a[current].size(); ++i)
        {
            next = a[current][i];
            
            if (!visited[next])
            {
                q.push(next);
                d[next] = d[current] + 6; // 6 is the constant distance between 2 nodes
                
                visited[next] = true;
            }
        }
    
        q.pop();
    }

    for (int v = 1; v < n + 1; ++v)
    {
        if (visited[v] == false) // value -1 for non-connected nodes
        {
            d[v] = -1;
        }
    }

return d;
}

void Output()
{    
    vector<int> res = shortest_reach(start);

    ofstream f;
    f.open(outputFile);
    
    for (int i = 1; i < n + 1; ++i)
    {
        if (!(i == start))
        {
            f << res[i] << " ";
        }
    }

    f.close();
}


int main()
{
    Input();
    Output();

    return 0;
}
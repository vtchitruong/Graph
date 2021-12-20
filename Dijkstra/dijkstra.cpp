#include <iostream>
#include <vector>
#include <fstream>
#include <stack>

#define inputFile "dijkstra.inp"
#define outpuFile "dijkstra.out"

using namespace std;

int vertices, edges, start, finish; // total number of vertices or edges
vector<vector<int>> a; // adjacent matrix

vector<bool> visited;
vector<int> d; // distance
vector<int> trace;
const int INF = 2E9; // infinity

//-----------------------------------------------------------------------------
void Input()
{
    ifstream f;
    f.open(inputFile);

    f >> vertices >> edges >> start >> finish;

    a.resize(vertices + 1, vector<int>(vertices + 1, INF)); // init adjacent matrix
    
    // read edges
    for (int e = 0; e < edges; ++e)
    {
        int u, v, len; // length        
        f >> u >> v >> len;
        a[u][v] = len;        
    }

    f.close();
}

//-----------------------------------------------------------------------------
void Init()
{
    // a vertex is visited or not
    visited.resize(vertices + 1, false);

    // d[v] is the minimum distance from start to v
    d.resize(vertices + 1, INF);
    d[start] = 0;

    // trace[v] = u means that u is followed by v, or we have to travel from u to v
    trace.resize(vertices + 1);
}

//-----------------------------------------------------------------------------
// Find the minimum distance in vector d of un-visited vertex
int minDistance()
{    
    int min_d = INF;
    int min_index = 0;
    
    for (int v = 1; v < vertices + 1; ++v)
    {
        if (!visited[v])
            if (d[v] < min_d)
            {
                min_d = d[v];
                min_index = v;                
            }
    }

    return min_index;
}

//-----------------------------------------------------------------------------
void Dijkstra()
{
    Init();

    while (true)
    {
        // find the vertex which has minimum distance from start for next travel from it
        int u = minDistance();
        
        // cannot travel anymore or reach the finish
        if (u == 0 || u == finish) break;

        visited[u] = true;

        for (int v = 1; v < vertices + 1; ++v)
        {
            if (!visited[v])
                if (d[u] + a[u][v] < d[v])
                {
                    d[v] = d[u] + a[u][v]; // update the minimum distance
                    trace[v] = u; // for output path
                }
        }
    }
}

//-----------------------------------------------------------------------------
void Output()
{
    stack<int> p; // path

    if (d[finish] == INF) // cannot reach finish
    {
        p.push(-1);
    }
    else
    {
        int f = finish; // temporary finish

        // trace back from finish to start for output path       
        while (f != start)
        {
            p.push(f);
            f = trace[f];
        }

        p.push(start);
    }

    ofstream f;
    f.open(outpuFile);

    f << d[finish] << endl;
    while (!p.empty())
    {
        f << p.top();
        if (p.size() != 1) f << ' ';
        p.pop();
    }

    f.close();
}

//-----------------------------------------------------------------------------
int main()
{
    Input();
    Dijkstra();
    Output();

    return 0;
}
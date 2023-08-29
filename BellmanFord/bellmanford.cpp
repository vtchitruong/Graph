#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <map>

#define inputFile "bf.inp"
#define outpuFile "bf.out"

using namespace std;

int vNum, eNum, start, finish; // number of vertices, number of edges
vector<vector<int>> edges;

vector<int> d; // distance
vector<int> trace;
const int INF = 2E9; // infinity
bool negativeCycle = false; // the graph has some negative cycle or not

//-----------------------------------------------------------------------------
void Input()
{
    ifstream f;
    f.open(inputFile);

    f >> vNum >> eNum >> start >> finish;

    // read edges
    for (int i = 0; i < eNum; ++i)
    {
        int u, v, len; // length
        f >> u >> v >> len;
        vector<int> edge{u, v, len};
        edges.push_back(edge);
    }

    f.close();
}

//-----------------------------------------------------------------------------
void Init()
{
    // d[v] is the minimum distance from start to v
    d.resize(vNum + 1, INF);
    d[start] = 0;

    // trace[v] = u means that u is followed by v, or we have to travel from u to v
    trace.resize(vNum + 1);
}

//-----------------------------------------------------------------------------
void Show_d()
{
    for (int i = 0; i < d.size(); ++i)
    {
        cout << d[i] << ' ';
    }
    cout << endl;
}

//-----------------------------------------------------------------------------
void BellmanFord()
{
    Init();

    for (int k = 1; k < vNum; ++k) // k <= vNum - 1
    {
        for (int i = 0; i < edges.size(); ++i)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            int weight = edges[i][2] ; // weight of u -> v

            if (d[u] != INF)
                if (d[u] + weight < d[v])
                {
                    d[v] = d[u] + weight;
                    trace[v] = u;
                }
        }
    }

    cout << "Array d after iterating k times" << endl;
    Show_d();

    for (int i = 0; i < edges.size(); ++i)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int weight = edges[i][2] ; // weight of u -> v

        if (d[u] != INF)
            if (d[u] + weight < d[v])
            {
                d[v] = d[u] + weight;                
                negativeCycle = true; // the graph has some negative cycle
            }
    }

    cout << "Array d after iterating 1 more times" << endl;
    Show_d();
}

//-----------------------------------------------------------------------------
void Output()
{
    stack<int> p; // path

    if (d[finish] == INF) // cannot reach finish
    {
        p.push(-1);
    }
    else if (negativeCycle)
    {
        p.push(-2);
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
    for (auto i = edges.begin(); i != edges.end(); ++i)
    {
        cout << (*i)[0] << ' ' << (*i)[1] << ' ' << (*i)[2] << endl;
    }

    BellmanFord();
    Output();

    return 0;
}
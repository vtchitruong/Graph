#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <stack>

#define inputFile "dijkstra.inp"
#define outputFile "dijkstra.out"

using namespace std;

int vertices, edges, start, finish;
vector<vector<pair<int, int>>> graph;

vector<int> d; // distance
vector<int> trace;

const int INF = INT_MAX;

void Input()
{
    ifstream f;
    f.open(inputFile);

    f >> vertices >> edges >> start >> finish;

    graph.resize(vertices + 1);

    int u, v, weight;
    for (int i = 0; i < edges; ++i)
    {
        f >> u >> v >> weight;
        graph[u].push_back({v, weight});
    }

    f.close();
}

void Init()
{
    // d[v] là khoảng cách ngắn nhất từ start đến v
    d.resize(vertices + 1, INF);
    d[start] = 0;

    // trace[v] = u nghĩa là trước đỉnh v là đỉnh u
    trace.resize(vertices + 1);
}

void Dijkstra()
{
    // Khai báo biến q kiểu set, mỗi phần tử là một pair
    // với first là khoảng cách d, second là đỉnh v.
    // Nghĩa là, tại đỉnh v, khoảng cách ngắn nhất từ start đến v là d.
    set<pair<int, int>> q;
    q.insert({0, start});
    
    while (!q.empty())
    {
        // Xét đỉnh u của phần tử đầu tiên
        int u = q.begin()->second;
        q.erase(q.begin());

        // Dừng thuật toán khi đã đến đích
        if (u == finish)
            break;

        // Duyệt các đỉnh kề với đỉnh u
        for (int i = 0; i < graph[u].size(); ++i)
        {
            int v = graph[u][i].first;
            int w = graph[u][i].second;

            if (d[u] + w < d[v])
            {
                // Xóa phần tử có giá trị d[v] trong hàng đợi
                q.erase({d[v], v});

                // Lưu khoảng cách ngắn nhất mới
                d[v] = d[u] + w;

                // Lưu vết
                trace[v] = u;

                // Thêm vào hàng đợi
                q.insert({d[v], v});
            }
        }
    }
}

//-----------------------------------------------------------------------------
void Output()
{
    stack<int> path;

    if (d[finish] != INF)
    {
        int fn = finish; // biến tạm

        // Dựa vào mảng trace, cho fn "lùi" dần về start
        while (fn != start)
        {
            path.push(fn);
            fn = trace[fn];
        }

        path.push(start);
    }

    ofstream f;
    f.open(outputFile);

    f << d[finish] << endl;
    while (!path.empty())
    {
        f << path.top();
        if (path.size() != 1) f << ' ';
        path.pop();
    }

    f.close();
}

//-----------------------------------------------------------------------------
int main()
{
    Input();
    Init();
    Dijkstra();
    Output();
    return 0;
}
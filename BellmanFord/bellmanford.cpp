#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <map>
#include <iomanip>

#define inputFile "bf1.inp"
#define outpuFile "bf1.out"

using namespace std;

int numberOfVertices, numberOfEdges, start, finish;
vector<vector<int>> edges;

vector<int> d;
vector<int> trace;
const int INF = 2E9; // infinity
bool negativeCycle = false;

void Input()
{
    ifstream f;
    f.open(inputFile);

    f >> numberOfVertices >> numberOfEdges >> start >> finish;

    for (int i = 0; i < numberOfEdges; ++i)
    {
        int u, v, w; // weight
        f >> u >> v >> w;
        vector<int> edge{u, v, w};
        edges.push_back(edge);
    }

    f.close();
}

void Show_d()
{
    for (int i = 1; i < d.size(); ++i)
    {
        cout << "(" << d[i] << ", " << trace[i] << ") |";
    }
    cout << endl;
}

void BellmanFord()
{
    // Bước 0:
    // Khởi tạo d[v] là khoảng cách ngắn nhất từ start đến v
    d.resize(numberOfVertices + 1, INF);
    d[start] = 0;

    // Khởi tạo trace[v] = u, nghĩa là trước đỉnh v là đỉnh u
    trace.resize(numberOfVertices + 1, 0);

    // Bước 1:
    // Lặp (v - 1) lần cập nhật khoảng cách (relaxation)
    for (int i = 1; i <= numberOfVertices - 1; ++i)
    {
        for (int j = 0; j < numberOfEdges; ++j)
        {
            int u = edges[j][0];
            int v = edges[j][1];
            int weight = edges[j][2] ;

            // Xét xem có đường đi từ start đến u hay không
            if (d[u] != INF)
            {
                // Xét đường đi từ start đến v mà thông qua u liệu có thể ngắn hơn được hay không
                if (d[u] + weight < d[v])
                {
                    d[v] = d[u] + weight;
                    trace[v] = u;
                }
            }
        }
    }    

    // Bước 2: Phát hiện chu trình mang trọng số âm
    for (int i = 0; i < numberOfEdges; ++i)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int weight = edges[i][2] ;

        if (d[u] != INF)
        {
            // Nếu weight là âm thì khoảng cách d sẽ bị giảm
            // Suy ra có chu trình âm
            if (d[u] + weight < d[v])
            {          
                negativeCycle = true;
                d[v] = d[u] + weight;
                trace[v] = u;
                
                return;
            }
        }
    }
}

void Output()
{
    stack<int> path;

    if (d[finish] == INF)
    {
        path.push(-1);
    }
    else if (negativeCycle)
    {
        path.push(-2);
    }
    else
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
    f.open(outpuFile);

    // Nếu không phải giá trị -1 hoặc -2
    if (path.top() >= 0)
    {
        // thì output đường đi ngắn nhất
        f << d[finish] << endl;
    
        while (!path.empty())
        {
            f << path.top();
            if (path.size() != 1) f << ' ';
            path.pop();
        }
    }
    else
    {
        f << path.top();
    }   
    
    f.close();
}

int main()
{
    Input();
    BellmanFord();
    Output();

    return 0;
}
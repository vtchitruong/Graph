#include <iostream>
#include <vector>
#include <stack>

#define input_file "floyd-warshall.inp"
#define output_file "floyd-warshall.out"

using namespace std;

int number_of_vertices, number_of_edges, start, finish;
vector<vector<int>> graph;

// Mảng trace dùng để lưu vết đường đi
// trace[u][v] = k nghĩa là: u -> k -> v
vector<vector<int>> trace;


void input()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen(input_file, "r", stdin);
    cin >> number_of_vertices >> number_of_edges >> start >> finish;

    graph.resize(number_of_vertices + 1, vector<int>(number_of_vertices + 1, 1e9));

    for (int u = 1; u < number_of_vertices + 1; ++u)
    {
        graph[u][u] = 0;
    }

    int u, v, w;
    for (int i = 0; i < number_of_edges; ++i)
    {
        cin >> u >> v >> w;
        graph[u][v] = w;
    }
}


void floyd_warshall()
{
    // Khởi tạo mảng trace
    trace.resize(number_of_vertices + 1, vector<int>(number_of_vertices + 1, -1));

    for (int u = 1; u < number_of_vertices + 1; ++u)
    {
        for (int v = 1; v < number_of_vertices + 1; ++v)
        {
            if (graph[u][v] != 1e9 && u != v)
                trace[u][v] = u;
        }
    }

    // Duyệt từng đỉnh trung gian k
    for (int k = 1; k < number_of_vertices + 1; ++k)
    {
        // Duyệt từng cặp đỉnh u, v
        for (int u = 1; u < number_of_vertices + 1; ++u)
        {
            for (int v = 1; v < number_of_vertices + 1; ++v)
            {
                // Nếu có thể đi u -> k và k -> v nhanh hơn so với u -> v
                if (graph[u][k] != 1e9 && graph[k][v] != 1e9 && graph[u][k] + graph[k][v] < graph[u][v])
                {
                    // thi cập nhật lại khoảng cách u -> v
                    graph[u][v] = graph[u][k] + graph[k][v];

                    // Lưu vết đường đi u -> v thông qua k (u -> k -> v)
                    trace[u][v] = trace[k][v];
                }
            }
        }
    }
}


void output()
{
    freopen(output_file, "w", stdout);

    // Nếu không có đường đi từ đỉnh start đến đỉnh finish
    if (graph[start][finish] == 1e9)
    {
        cout << "No path found" << '\n';
        return;
    }

    // Ngược lại, có đường đi, thì dựa vào mảng trace để truy vết đường đi từ đỉnh finish về đỉnh start
    stack<int> path;

    // Biến tạm fn để lưu đỉnh hiện hành
    int fn = finish;

    // Trong khi fn chưa về đến đỉnh start
    while (fn != start)
    {
        // Thêm đỉnh fn vào đường đi
        path.push(fn);

        // Lùi về đỉnh trước đó
        fn = trace[start][fn];
    }
    
    // Thêm đỉnh start vào đường đi
    path.push(start);

    // In ra khoảng cách ngắn nhất từ đỉnh start đến đỉnh finish
    cout << graph[start][finish] << '\n';

    // In ra đường đi ngắn nhất từ đỉnh start đến đỉnh finish
    while (!path.empty())
    {
        cout << path.top();
        if (path.size() != 1) cout << ' ';
        path.pop();
    }
}


int main()
{
    input();
    floyd_warshall();
    output();
    return 0;
}
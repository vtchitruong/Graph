#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <stack>

#define input_file "dijkstra.inp"
#define output_file "dijkstra.out"

using namespace std;

int number_of_vertices, number_of_edges, start, finish;
vector<vector<pair<int, int>>> graph;

// Mảng D dùng để lưu khoảng cách ngắn nhất từ đỉnh start đến các đỉnh khác
// D[v] = d nghĩa là: khoảng cách ngắn nhất từ đỉnh start đến đỉnh v là d
vector<int> D;

// Mảng trace dùng để lưu vết đường đi
// trace[v] = u nghĩa là: u -> v
vector<int> trace;

const int INF = INT_MAX;

void input()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen(input_file, "r", stdin);

    cin >> number_of_vertices >> number_of_edges >> start >> finish;

    graph.resize(number_of_vertices + 1);

    int u, v, weight;
    for (int i = 0; i < number_of_edges; ++i)
    {
        cin >> u >> v >> weight;
        graph[u].push_back({v, weight});
    }
}


void dijkstra()
{
    // Khởi tạo mảng khoảng cách D
    D.resize(number_of_vertices + 1, INF);
    D[start] = 0;

    // Khởi tạo mảng trace
    trace.resize(number_of_vertices + 1, -1);

    // Biến q có kiểu set, mỗi phần tử là một pair
    // với first là khoảng cách d, second là đỉnh v.
    // Nghĩa là, tại đỉnh v, khoảng cách ngắn nhất từ start đến đỉnh v là d.
    set<pair<int, int>> q;
    q.insert({0, start});
    
    // Trong khi q vẫn còn phần tử
    while (!q.empty())
    {
        // Lấy ra đỉnh u có khoảng cách ngắn nhất từ start (vì set đã sắp xếp theo khoảng cách)
        int u = q.begin()->second;
        q.erase(q.begin());

        // Dừng thuật toán khi đã đến đích
        if (u == finish)
            break;

        // Duyệt từng đỉnh v kề với đỉnh u
        for (int i = 0; i < graph[u].size(); ++i)
        {
            // v là đỉnh kề với u
            int v = graph[u][i].first;

            // w là trọng số của cạnh u -> v
            int w = graph[u][i].second;

            // Nếu có thể đi start -> u -> v nhanh hơn so với start -> v
            if (D[u] + w < D[v])
            {
                // Nếu v đã có trong q thì xóa phần tử liên quan
                q.erase({D[v], v});

                // Cập nhật lại khoảng cách ngắn nhất từ đỉnh start đến đỉnh v
                D[v] = D[u] + w;

                // Lưu vết đường đi từ start đến v thông qua u
                trace[v] = u;

                // Thêm v vào q với khoảng cách ngắn nhất từ start đến v là d[v]
                q.insert({D[v], v});
            }
        }
    }
}


void output()
{
    freopen(output_file, "w", stdout);

    // Nếu không có đường đi từ start đến finish
    if (D[finish] == INF)
    {
        cout << "No path found" << '\n';
        return;
    }

    // Ngược lại, có đường đi từ start đến finish, thì dựa vào mảng trace để truy vết đường đi
    stack<int> path;

    // Biến tạm fn để lưu đỉnh hiện hành    
    int fn = finish;

    // Trong khi fn chưa về đến đỉnh start
    while (fn != start)
    {
        // Thêm đỉnh fn vào đường đi
        path.push(fn);

        // Lùi về đỉnh trước đó
        fn = trace[fn];
    }

    // Thêm đỉnh start vào đường đi
    path.push(start);

    // In ra khoảng cách ngắn nhất từ đỉnh start đến đỉnh finish
    cout << D[finish] << '\n';

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
    dijkstra();
    output();
    return 0;
}
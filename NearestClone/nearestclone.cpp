#include <iostream>
#include <vector>
#include <queue>

#define input_file "nearestclone1.inp"
#define output_file "nearestclone1.out"

using namespace std;

int node_number, edge_number;

// Danh sách kề
vector<vector<int>> A;

// Mảng lưu màu của các đỉnh
vector<int> colors;

// Màu theo yêu cầu
int color_required;

// output
int min_distance = INT_MAX;


void input()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen(input_file, "r", stdin);

    cin >> node_number >> edge_number;

    A.resize(node_number + 1);

    int u, v;
    for (int i = 0; i < edge_number; ++i)
    {
        cin >> u >> v;
        A[u].push_back(v);
        A[v].push_back(u);
    }

    colors.resize(node_number + 1, 0);

    for (int u = 1; u < node_number + 1; ++u)
    {

        cin >> colors[u];
    }

    cin >> color_required;
}


int bfs(int s, vector<bool>& visited)
{
    // Khai báo hàng đợi chứa các đỉnh kèm khoảng cách tính từ đỉnh s
    queue<pair<int, int>> q;

    // Đẩy đỉnh s kèm khoảng cách (tính từ đỉnh s) vào hàng đợi
    q.push({s, 0});

    // Đánh dấu đỉnh s đã duyệt
    visited[s] = true;

    // Đỉnh current và khoảng cách tính từ đỉnh s
    pair<int, int> current;

    // Trong khi hàng đợi còn phần tử
    while (!q.empty())
    {
        // Lấy phần tử ở đầu hàng đợi
        current = q.front();
        q.pop();

        // Duyệt từng đỉnh kề với đỉnh current
        for (int v : A[current.first])
        {
            // Nếu đỉnh v chưa duyệt
            if (!visited[v])
            {
                // Kiểm tra có đúng màu yêu cầu không
                if (colors[v] == color_required)
                {
                    // Nếu đúng màu yêu cầu thì trả về khoảng cách (tính từ đỉnh s)
                    return current.second + 1;
                }
                
                // Đánh dấu đã duyệt đỉnh v
                visited[v] = true;

                // Nạp đỉnh và khoảng cách vào hàng đợi
                q.push({v, current.second + 1 });
            }
        }
    }
    
    // Từ đỉnh s không loang đến được đỉnh nào cùng màu
    return INT_MAX;
}


void process()
{
    // Khởi tạo giá trị false cho toàn mảng vst (visited)
    vector<bool> vst(node_number + 1, false);

    int tmp_distance;

    // Duyệt từng đỉnh bằng biến u
    for (int u = 1; u < node_number + 1; ++u)
    {
        // Nếu màu của đỉnh u đúng theo yêu cầu
        if (colors[u] == color_required)
        {
            // Thiết lập mảng visited về lại trạng thái ban đầu
            fill(vst.begin(), vst.end(), false);

            // Thực hiện bfs() để loang đến đỉnh có cùng màu
            tmp_distance = bfs(u, vst);

            // Nếu có khoảng cách bằng 1
            if (tmp_distance == 1)
            {
                // thì output ngay kết quả
                min_distance = 1;
                return;
            }

            // Ngược lại, ghi nhận khoảng cách nhỏ hơn
            min_distance = min(min_distance, tmp_distance);
        }
    }
}


void output()
{
    freopen(output_file, "w", stdout);

    if (min_distance == INT_MAX)
    {
        cout << -1;
    }
    else
    {
        cout << min_distance;
    }
}


int main()
{
    input();
    process();
    output();

    return 0;
}
#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>

#define input_file "dfs.inp"
#define output_file "dfs.out"

using namespace std;

// số đỉnh, số cạnh, đỉnh xuất phát, đỉnh đích
int vertex, edge, start, finish;

// danh sách kề
vector<vector<int>> A;

// Mảng dùng để truy ngược, trace[u] = v nghĩa là trước đỉnh u là đỉnh v
vector<int> trace;

void input()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen(input_file, "r", stdin);

    cin >> vertex >> edge >> start >> finish;

    // Khởi tạo danh sách đỉnh kề
    A.resize(vertex + 1);

    int u, v;
    
    // Đọc từng dòng và nạp các đỉnh vào hàng A[u] tương ứng
    // Hàng A[u] chứa các đỉnh v kề với đỉnh u
    for (int i = 0; i < edge; ++i)
    {
        cin >> u >> v;
        A[u].push_back(v);
    }
}


void init()
{
    // Khởi tạo mảng trace gồm toàn 0, nghĩa là tất cả đỉnh đều chưa có đỉnh liền trước
    trace.resize(vertex + 1, 0);
    
    // Trước đỉnh start không có đỉnh nào
    trace[start] = -1;
}


void dfs(int current)
{
    // Duyệt các đỉnh kề với đỉnh current
    for (vector<int>::iterator i = A[current].begin(); i != A[current].end(); ++i)
    {
        // Nếu đỉnh *i chưa ghé thăm thì đánh dấu ghé thăm *i bằng mảng trace
        // rồi xem *i là đỉnh gốc, gọi đệ quy đối với đỉnh *i
        if (!trace[*i])
        {
            trace[*i] = current;
            dfs(*i);
        }
    }
}


void process()
{
    // Khởi tạo mảng trace
    init();

    // Thực hiện duyệt theo chiều sâu, xuất phát từ đỉnh start
    dfs(start);
}


void output()
{
    // Khai báo ngăn xếp path lưu các đỉnh của đường đi cần tìm
    stack<int> path; 

    // Dùng tmp_finish để không làm mất giá trị của finish khi truy ngược
    int tmp_finish = finish;

    // Nếu có đường đi đến đỉnh finish thì mới thực hiện truy ngược trace
    if (trace[tmp_finish])
    {
        // Dựa vào mảng trace, cho tmp_finish "lùi" dần về start
        while (tmp_finish != start)
        {
            // Trong khi chưa đụng đỉnh start, thì nạp đỉnh tmp_finish vào đường đi
            path.push(tmp_finish);

            // "Lùi" tmp_finish về đỉnh liền trước đó
            tmp_finish = trace[tmp_finish];
        }

        // Nạp đỉnh start vào đường đi
        path.push(start);
    }
    
    freopen(output_file, "w", stdout);

    // Nếu không có phần tử nào trong ngăn xếp path
    // thì in ra -1, nghĩa là không có đường đi
    if (path.empty())
    {
        cout << -1;
    }
    else
    {
        // Trong khi ngăn xếp path vẫn còn phần tử
        while (!path.empty())
        {
            // thì in ra phần tử nằm ở đầu ngăn xếp
            cout << path.top();

            // nếu ngăn xếp path còn hơn một phần tử thì in dấu phân cách
            if (path.size() != 1)
                cout << " --> ";
            
            // rồi xóa bỏ phần tử đầu ngăn xếp này
            path.pop();
        }
    }
}


// Hàm in ra mảng trace
void show_trace()
{
    for (int u = 1; u < vertex + 1; ++u)
    {
        cout << setw(4) << u << ' '; 
    }

    cout << endl;

    for (int u = 1; u < vertex + 1; ++u)
    {
        cout << setw(4) << trace[u] << ' '; 
    }
}

int main()
{
    input();
    process();
    output();

    return 0;
}
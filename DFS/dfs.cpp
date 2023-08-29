#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

#define inputFile "dfs.inp"
#define outputFile "dfs.out"

using namespace std;

// số đỉnh, số cạnh, đỉnh xuất phát, đỉnh đích
int vertex, edge, start, finish;

// danh sách kề
vector<vector<int>> a;

// Mảng dùng để truy ngược, trace[v] = u nghĩa là trước đỉnh v là đỉnh u
vector<int> trace;

void Input()
{
    ifstream f;
    f.open(inputFile);

    f >> vertex >> edge >> start >> finish;

    // Khởi tạo danh sách đỉnh kề
    a.resize(vertex + 1);

    int u, v;
    
    // Đọc từng dòng và nạp các đỉnh vào hàng a[u] tương ứng
    // Hàng a[u] chứa các đỉnh v kề với đỉnh u
    for (int i = 1; i < edge + 1; ++i)
    {
        f >> u >> v;
        a[u].push_back(v);
    }

    f.close();
}

// Hàm khởi tạo
void Init()
{
    // Khởi tạo mảng trace gồm toàn 0, nghĩa là các đỉnh trong trace đều chưa có đỉnh liền trước
    trace.resize(vertex + 1, 0);
    
    // Trước đỉnh start không có đỉnh nào
    trace[start] = -1;
}

// Hàm Dfs thực hiện đệ quy, xem current là đỉnh gốc
void Dfs(int current)
{
    // Duyệt các đỉnh kề với đỉnh current
    for (vector<int>::iterator i = a[current].begin(); i != a[current].end(); ++i)
    {
        // Nếu đỉnh *i chưa ghé thăm thì đánh dấu ghé thăm *i bằng mảng trace
        // rồi xem *i là đỉnh gốc, gọi đệ quy tiếp từ đỉnh *i
        if (!trace[*i])
        {
            trace[*i] = current;
            Dfs(*i);
        }
    }
}

// Hàm Process tổng hợp các thao tác cần thực hiện
void Process()
{
    // Khởi tạo mảng trace
    Init();

    // Thực hiện duyệt theo chiều sâu, xuất phát từ đỉnh start
    Dfs(start);
}

void Output()
{
    // Khai báo stack path lưu các đỉnh của đường đi cần tìm
    stack<int> path; 

    // Dùng tmpFinish để không làm mất giá trị của finish khi truy ngược
    int tmpFinish = finish;

    // Nếu có đường đi đến đỉnh finish thì mới thực hiện truy ngược trace
    if (trace[tmpFinish])
    {
        // Dựa vào mảng trace, cho tmpFinish "lùi" dần về start
        while (tmpFinish != start)
        {
            // Trong khi chưa đụng đỉnh start, thì nạp đỉnh tmpFinish vào đường đi
            path.push(tmpFinish);

            // "Lùi" tmpFinish về đỉnh liền trước đó
            tmpFinish = trace[tmpFinish];
        }

        // Nạp đỉnh start vào đường đi
        path.push(start);
    }

    ofstream f;
    f.open(outputFile);    

    if (path.empty())
    {
        // Nếu không có phần tử nào trong stack path
        // thì in ra -1, nghĩa là không có đường đi
        f << -1;
    }
    else
    {
        // Duyệt stack path và ghi các đỉnh vào file
        while (!path.empty())
        {
            f << path.top() << " --> ";
            path.pop();
        }
    }

    f.close();
}

int main()
{
    Input();
    Process();
    Output();

    return 0;
}
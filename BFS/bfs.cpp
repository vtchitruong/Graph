#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <iomanip>

#define inputFile "bfs.inp"
#define outputFile "bfs.out"

using namespace std;

// số đỉnh, số cạnh, đỉnh xuất phát, đỉnh đích
int vertex, edge, start, finish;

// danh sách kề
vector<vector<int>> a;

// Mảng dùng để truy ngược, trace[u] = v nghĩa là trước đỉnh u là đỉnh v
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

void Bfs()
{
    // Khởi tạo queue, nạp đỉnh start vào queue
    queue<int> q;
    q.push(start);

    // current là biến tạm, chỉ đỉnh hiện hành
    int current;
    
    // Trong khi queue vẫn còn phần tử
    while (!q.empty())
    {
        // thì gán phần tử nằm ở đầu queue vào biến tạm current
        current = q.front();

        // Duyệt các đỉnh kề với đỉnh current
        for (vector<int>::iterator i = a[current].begin(); i != a[current].end(); ++i)
        {
            // Nếu đỉnh *i chưa ghé thăm thì đánh dấu ghé thăm *i bằng mảng trace
            // rồi đẩy *i vào queue
            if (!trace[*i])
            {
                trace[*i] = current;
                q.push(*i);
                
            }
        }

        // Xóa bỏ phần tử nằm ở đầu queue, là đỉnh current
        q.pop();
    }
}

// Hàm Process tổng hợp các thao tác cần thực hiện
void Process()
{
    // Khởi tạo mảng trace
    Init();

    // Thực hiện duyệt theo chiều rộng
    Bfs();
}

// Hàm in kết quả ra file
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
        // Trong khi stack path vẫn còn phần tử
        while (!path.empty())
        {
            // thì in ra phần tử nằm ở đầu stack
            f << path.top() << " --> ";

            // rồi xóa bỏ phần tử đầu stack này
            path.pop();
        }
    }

    f.close();
}

// Hàm in ra console mảng trace
void ShowTrace()
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
    Input();
    Process();
    Output();

    ShowTrace();

    return 0;
}

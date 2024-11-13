#include <iostream>
#include <vector>
#include <stack>

#define input_file "forest.inp"
#define output_file "forest.out"

using namespace std;

const int MAX = 1000;

int row_number, col_number;
vector<string> forest;

// Ô xuất phát và ô kết thúc
pair<int, int> start, finish;

// Mảng trace dùng để truy vết đường đi
vector<vector<int>> trace;

// Mảng lưu 4 cách di chuyển: lên, xuống, trái, phải
vector<pair<int,int>> steps = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};


void input()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen(input_file, "r", stdin);

    cin >> row_number >> col_number;

    // Đọc từng hàng và đưa vào mảng forest
    string row;
    for (int r = 0; r < row_number; ++r)
    {
        cin >> row;
        forest.push_back(row);
    }
}


void init()
{
    // Xác định vị trí của nhà thám hiểm
    for (int r = 0; r < row_number; r++)
    {
        int c = forest[r].find('E');

        // Nếu tìm thấy nhà thám hiểm (tức ký tự E)
        if (c != string::npos)
        {
            // thì ghi nhận đó là ô xuất phát
            start.first = r;
            start.second = c;
            break;
        }
    }

    // Khởi tạo giá trị -1 cho toàn bộ mảng trace
    trace.resize(row_number, vector<int>(col_number, -1));

    for (int r = 0; r < row_number; ++r)
    {
        trace[r].resize(col_number, -1);
    }
}


void dfs(pair<int, int> current)
{
    // Điều kiện dừng đệ quy DFS là nhà thám hiểm đã đến được bìa rừng
    if (current.first == 0 || current.first == row_number - 1 || current.second == 0 || current.second == col_number - 1)
    {
        // Ghi nhận vị trí ở bìa rừng là ô kết thúc
        finish.first = current.first;
        finish.second = current.second;
        return;
    }

    pair<int, int> next;

    // Duyệt từng cách di chuyển
    for (int s = 0; s < 4; ++s)
    {
        next.first = current.first + steps[s].first;
        next.second = current.second + steps[s].second;

        // Nếu nhà thám hiểm vẫn còn trong bên trong phạm vi khu rừng
        // và nếu ô next chưa đánh dấu đã duyệt
        // và nếu ô next không có bẫy
        if (next.first >= 0)
            if (next.first < row_number)
                if (next.second >= 0)
                    if (next.second < col_number)
                        if (trace[next.first][next.second] == -1)
                            if (forest[next.first][next.second] == 'O')
                            {
                                // thì đánh dấu ô next đã duyệt và dùng để truy vết sau này
                                // bằng cách dùng công thức để gộp toạ độ hàng và toạ độ cột vào chung một giá trị
                                trace[next.first][next.second] = current.second * MAX + current.first;

                                // Gọi đệ quy đối với ô next
                                dfs(next);
                            }
    }
}


void process()
{
    init();
    dfs(start);
}


void output()
{
    // Đường đi kết quả
    stack<pair<int, int>> path;

    // Nạp ô kết thúc (ở bìa rừng) vào ngăn xếp path
    path.push(finish);

    // Dựa vào mảng trace để truy vết các ô nằm trước ô kết thúc
    while (trace[finish.first][finish.second] != -1)
    {
        // Tách giá trị đã gộp ở dfs() trở lại thành hai thành phần toạ độ riêng lẻ
        int r = trace[finish.first][finish.second] % MAX;
        int c = trace[finish.first][finish.second] / MAX;

        // Đẩy toạ độ vào ngăn xếp
        path.push({r, c});

        // Tiếp tục lùi ô kết thúc đến vị trí mới
        finish.first = r;
        finish.second = c;
    }

    freopen(output_file, "w", stdout);

    while (!path.empty())
    {
        cout << path.top().first << ' ' << path.top().second;
        if (path.size() != 1) cout << '\n';
        path.pop();
    }
}


int main()
{
    input();
    process();
    output();   

    return 0;
}
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

#define input_file "robotmove.inp"
#define output_file "robotmove.out"

using namespace std;

int row_number, col_number;
vector<vector<char>> maze;

// Ô xuất phát và ô kết thúc
pair<int,int> start, finish;

// Mảng trace dùng để truy vết đường đi
vector<vector<char>> trace;


void input()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen(input_file, "r", stdin);

    cin >> row_number >> col_number >> start.first >> start.second >> finish.first >> finish.second;
    
    // Khởi tạo ma trận maze gồm toàn phần tử 0
    maze.resize(row_number + 1, vector<char>(col_number + 1, 0));

    // Đọc từng hàng của input và đưa vào mảng maze
    string row;
    for (int r = 1; r < row_number + 1; ++r)
    {        
        cin >> row;

        for (int c = 1; c < col_number + 1; ++c)
        {
            if (row[c - 1] == '1') maze[r][c] = 1;
        }        
    }
}


void init()
{
    // Khởi tạo giá trị 'N' cho toàn bộ mảng trace
    trace.resize(row_number + 1, vector<char>(col_number + 1, 'N'));

    // Ô xuất phát được đánh dấu bằng ký tự 'S'
    trace[start.first][start.second] = 'S';
}


void bfs()
{
    // Hàng đợi chứa các ô cần duyệt
    queue<pair<int, int>> q;

    // Nạp ô xuất phát vào hàng đợi
    q.push(start);
    
    pair<int, int> current;
    pair<int, int> next;

    // Trong khi hàng đợi vẫn còn ô chờ duyệt
    while (!q.empty())
    {
        // Lấy ô ở đầu hàng đợi
        current = q.front();
        q.pop();

        // Dừng vòng lặp khi ô sắp duyệt là ô kết thúc, tức đã đến đích
        if (current == finish)
            return;

        // Thử đi lên một ô
        if (current.first > 1)
            if (maze[current.first - 1][current.second] == 0)
                if (trace[current.first - 1][current.second] == 'N')
                {
                    // Lấy toạ độ của ô trên
                    next = current;
                    next.first--;

                    // Đẩy vào hàng đợi
                    q.push(next);

                    // Đánh dấu đã duyệt bằng ký tự U: up
                    trace[next.first][next.second] = 'U';
                }
        
        // Thử đi xuống một ô
        if (current.first < row_number)
            if (maze[current.first + 1][current.second] == 0)
                if (trace[current.first + 1][current.second] == 'N')
                {
                    // Lấy toạ độ của ô dưới
                    next = current;
                    next.first++;

                    // Đẩy vào hàng đợi
                    q.push(next);

                    // Đánh dấu đã duyệt bằng ký tự D: down
                    trace[next.first][next.second] = 'D';
                }

        // Thử qua trái một ô
        if (current.second > 1)
            if (maze[current.first][current.second - 1] == 0)
                if (trace[current.first][current.second - 1] == 'N')
                {
                    // Lấy toạ độ của ô trái
                    next = current;
                    next.second--;

                    // Đẩy vào hàng đợi
                    q.push(next);

                    // Đánh dấu đã duyệt bằng ký tự L: left
                    trace[next.first][next.second] = 'L';
                }
        
        // Thử qua phải một ô
        if (current.second < col_number)
            if (maze[current.first][current.second + 1] == 0)
                if (trace[current.first][current.second + 1] == 'N')
                {
                    // Lấy toạ độ của ô phải
                    next = current;
                    next.second++;

                    // Đẩy vào hàng đợi
                    q.push(next);

                    // Đánh dấu đã duyệt bằng ký tự R: right
                    trace[next.first][next.second] = 'R';
                }
    }
}


void process()
{
    init();
    bfs();
}


void output()
{
    // Đường đi kết quả
    stack<pair<int, int>> path;

    if (trace[finish.first][finish.second] != 'N')
    {
        // Dựa vào mảng trace để truy vết các ô nằm trước ô kết thúc
        while (trace[finish.first][finish.second] != 'S')
        {
            // Đẩy ô kết thúc vào ngăn xếp path
            path.push(finish);

            // Tiếp tục lùi ô kết thúc đến vị trí mới
            switch (trace[finish.first][finish.second])
            {
                case 'U': finish.first++;
                    break;
                case 'D': finish.first--;
                    break;
                case 'L': finish.second++;
                    break;
                case 'R': finish.second--;
                    break;
            }
        }

        // Đẩy ô xuất phát vào ngăn xếp
        path.push(start);
    }

    freopen(output_file, "w", stdout);

    if (path.empty())
    {
        cout << -1;
    }
    else
    {
        while (path.size() > 1)
        {
            cout << path.top().first << ' ' << path.top().second << '\n';
            path.pop();
        }

        cout << path.top().first << ' ' << path.top().second;
    }
}


int main()
{
    input();
    process();
    output();
    
    return 0;
}
import os
import sys

input_file = os.path.join(sys.path[0], 'forest.inp')
output_file = os.path.join(sys.path[0], 'forest.out')

MAX = 1000

row_number = 0
col_number = 0
forest = []

# Ô xuất phát và ô kết thúc
start = []
finish = []

# Mảng trace dùng để truy vết đường đi
trace = []

# Mảng lưu 4 cách di chuyển: lên, xuống, trái, phải
steps = [(-1, 0), (1, 0), (0, -1), (0, 1)]


def input_data():  
    global row_number, col_number, forest

    with open(input_file, 'r') as f:
        row_number, col_number = list(map(int, f.readline().split()))
        forest = [line.strip() for line in f.readlines()]


def init():
    global forest, start, trace
    
    # Xác định vị trí của nhà thám hiểm
    for r, row_data in enumerate(forest):
        # Nếu tìm thấy nhà thám hiểm (tức ký tự E)
        if 'E' in row_data:
            c = row_data.index('E')
            start = [r, c]
            break
    
    # Khởi tạo giá trị -1 cho toàn bộ mảng trace
    trace = [[-1 for col in range(col_number)] for row in range(row_number)]
 

def dfs(current):
    global MAX, finish, forest, trace, steps

    # Điều kiện dừng đệ quy DFS là nhà thám hiểm đã đến được bìa rừng
    if current[0] == 0 or current[0] == row_number - 1 or current[1] == 0 or current[1] == col_number - 1:
        # Ghi nhận vị trí ở bìa rừng là ô kết thúc
        finish = current
        return
    
    # Duyệt từng cách di chuyển
    for s in steps:
        next = [current[0] + s[0], current[1] + s[1]]

        # Nếu nhà thám hiểm vẫn còn trong bên trong phạm vi khu rừng
        # và nếu ô next chưa đánh dấu đã duyệt
        # và nếu ô next không có bẫy
        if 0 <= next[0] < row_number and 0 <= next[1] < col_number:
            if trace[next[0]][next[1]] == -1:
                if forest[next[0]][next[1]] == 'O':
                    # thì đánh dấu ô next đã duyệt và dùng để truy vết sau này
                    # bằng cách dùng công thức để gộp toạ độ hàng và toạ độ cột vào chung một giá trị
                    trace[next[0]][next[1]] = current[1] * MAX + current[0]
                    dfs(next)


def process():
    global start
    init()
    dfs(start)


def output():
    global finish, trace

    # Đường đi kết quả
    path = list()
    
    # Nạp ô kết thúc (ở bìa rừng) vào ngăn xếp path
    path.append(finish)
    
    # Dựa vào mảng trace để truy vết các ô nằm trước ô kết thúc
    while not trace[finish[0]][finish[1]] == -1:
        # Tách giá trị đã gộp ở dfs() trở lại thành hai thành phần toạ độ riêng lẻ
        r = trace[finish[0]][finish[1]] % MAX
        c = trace[finish[0]][finish[1]] // MAX

        # Đẩy toạ độ vào ngăn xếp
        path.append([r, c])

        # Tiếp tục lùi ô kết thúc đến vị trí mới
        finish = [r, c]

    with open(output_file, 'w') as f:
        result = '\n'.join([str(' '.join([str(number) for number in position])) for position in reversed(path)])    
        f.write(result)


if __name__ == '__main__':
    input_data()
    process() 
    output()
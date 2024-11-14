import os
import sys
import queue

input_file = os.path.join(sys.path[0], 'robotmove.inp')
output_file = os.path.join(sys.path[0], 'robotmove.out')

row_number = 0
col_number = 0
maze = []

# Ô xuất phát và ô kết thúc
start = []
finish = []

# Mảng trace dùng để truy vết đường đi
trace = []


def input_data():
    global row_number, col_number, maze, start, finish

    with open(input_file, 'r') as f:
        row_number, col_number, s_row, s_col, f_row, f_col = map(int, f.readline().split())
        start = [s_row, s_col]
        finish = [f_row, f_col]

        # read the remnaining lines for the maze
        lines = f.readlines()

        # Hàng có chỉ số 0
        maze.append([])

        for line in lines:
            line = '0' +  line.strip()            
            maze.append(list(map(int, line)))


def init():
    global trace
    
    # Khởi tạo giá trị 'N' cho toàn bộ mảng trace
    trace = [['N' for col in range(col_number + 1)] for row in range(row_number + 1)]
    
    # Ô xuất phát được đánh dấu bằng ký tự 'S'
    trace[start[0]][start[1]] = 'S'


def bfs():
    # Hàng đợi chứa các ô cần duyệt
    q = queue.Queue()

    # Nạp ô xuất phát vào hàng đợi
    q.put(start)

    # Trong khi hàng đợi vẫn còn ô chờ duyệt
    while q:
        # Lấy ô ở đầu hàng đợi
        current = q.get()

        # Dừng vòng lặp khi ô sắp duyệt là ô kết thúc, tức đã đến đích
        if current == finish:
            return

        # Thử đi lên một ô
        if current[0] > 1: # if robot could go up
            if maze[current[0] - 1][current[1]] == 0:
                if trace[current[0] - 1][current[1]] == 'N':
                    # Lấy toạ độ của ô trên
                    next = current.copy()
                    next[0] -= 1

                    # Đẩy vào hàng đợi
                    q.put(next)

                    # Đánh dấu đã duyệt bằng ký tự U: up
                    trace[next[0]][next[1]] = 'U'

        # Thử đi xuống một ô
        if current[0] < row_number:
            if maze[current[0] + 1][current[1]] == 0:
                if trace[current[0] + 1][current[1]] == 'N':
                    # Lấy toạ độ của ô dưới
                    next = current.copy()
                    next[0] += 1

                    # Đẩy vào hàng đợi
                    q.put(next)

                    # Đánh dấu đã duyệt bằng ký tự D: down
                    trace[next[0]][next[1]] = 'D'

        # Thử qua trái một ô
        if current[1] > 1:
            if maze[current[0]][current[1] - 1] == 0:
                if trace[current[0]][current[1] - 1] == 'N':
                    # Lấy toạ độ của ô trái
                    next = current.copy()
                    next[1] -= 1

                    # Đẩy vào hàng đợi
                    q.put(next)

                    # Đánh dấu đã duyệt bằng ký tự L: left
                    trace[next[0]][next[1]] = 'L'

        # Thử qua phải một ô
        if current[1] < col_number:
            if maze[current[0]][current[1] + 1] == 0:
                if trace[current[0]][current[1] + 1] == 'N':
                    # Lấy toạ độ của ô phải
                    next = current.copy()
                    next[1] += 1

                    # Đẩy vào hàng đợi
                    q.put(next)

                    # Đánh dấu đã duyệt bằng ký tự R: right
                    trace[next[0]][next[1]] = 'R'


def process():
    init();
    bfs();


def output():
    # Đường đi kết quả
    path = list()

    if trace[finish[0]][finish[1]] != 'N':
        # Dựa vào mảng trace để truy vết các ô nằm trước ô kết thúc
        while not trace[finish[0]][finish[1]] == 'S':
            # Đẩy ô kết thúc vào ngăn xếp path
            path.append(finish.copy())

            # Tiếp tục lùi ô kết thúc đến vị trí mới
            direction= trace[finish[0]][finish[1]]
            if direction== 'U':
                finish[0] += 1
            elif direction== 'D':
                finish[0] -= 1
            elif direction== 'L':
                finish[1] += 1
            elif direction== 'R':
                finish[1] -= 1
        
        # Đẩy ô xuất phát vào ngăn xếp
        path.append(start)
    
    with open(output_file, 'w') as f:
        if not path:
            f.write('-1')
        else:
            f.writelines([f'{path[i][0]} {path[i][1]}\n' for i in range(len(path) - 1, 0, -1)])
            f.write(f'{path[0][0]} {path[0][1]}')


if __name__ == '__main__':
    input_data()
    process()
    output()
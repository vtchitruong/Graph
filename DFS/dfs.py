import os
import sys
import queue
from collections import deque

input_file = os.path.join(sys.path[0], 'dfs.inp')
output_file = os.path.join(sys.path[0], 'dfs.out')

# số đỉnh, số cạnh, đỉnh xuất phát, đỉnh đích
vertex, edge, start, finish = 0, 0, 0, 0

# danh sách kề
a = []

# mảng dùng để truy ngược, trace[u] = v nghĩa là trước đỉnh u là đỉnh v
trace = []

def input_data():
    with open(input_file) as f:
        global vertex, edge, start, finish        
        vertex, edge, start, finish = list(map(int, f.readline().split()))

        global a
        # Khởi tạo danh sách đỉnh kề
        a = [[] for _ in range(vertex + 1)]

        # Đọc từng dòng và nạp các đỉnh vào hàng a[u] tương ứng
        # Hàng a[u] chứa các đỉnh v kề với đỉnh u
        for _ in range(edge):
            u, v = map(int, f.readline().split())
            a[u].append(v)


# Hàm khởi tạo 
def init():
    global trace
    
    # Khởi tạo mảng trace gồm toàn 0, nghĩa là các đỉnh trong trace đều chưa có đỉnh liền trước
    trace = [0] * (vertex + 1)
    
    # Trước đỉnh start không có đỉnh nào  
    trace[start] = -1


# Hàm dfs thực hiện đệ quy, xem current là đỉnh gốc
def dfs(current):
    global a, trace
        
    # Duyệt các đỉnh kề với đỉnh current
    for u in a[current]:
        # Nếu đỉnh u chưa ghé thăm thì đánh dấu ghé thăm u bằng mảng trace
        # rồi xem u là đỉnh gốc, gọi đệ quy tiếp từ đỉnh u
        if not trace[u]:
            trace[u] = current
            dfs(u)


# Hàm process tổng hợp các thao tác cần thực hiện
def process():
    # Khởi tạo mảng trace
    init()

    # Thực hiện duyệt theo chiều sâu, xuất phát từ đỉnh start
    dfs(start)


# Hàm in kết quả ra file
def output():
    # Khai báo stack path lưu các đỉnh của đường đi cần tìm
    # Module collections của Python không có kiểu stack
    # Thay vào đó deque dùng để biểu diễn cả queue lẫn stack
    path = deque()

    # Dùng tmpFinish để không làm mất giá trị của finish khi truy ngược
    tmpFinish = finish
    
    # Nếu có đường đi đến đỉnh finish thì mới thực hiện truy ngược trace
    if trace[tmpFinish]:
        # Dựa vào mảng trace, cho tmpFinish "lùi" dần về start
        while tmpFinish != start:
            # Trong khi chưa đụng đỉnh start, thì nạp đỉnh tmpFinish vào đường đi
            path.append(tmpFinish)
            
            # "Lùi" tmpFinish về đỉnh liền trước đó
            tmpFinish = trace[tmpFinish]
        
        # Nạp đỉnh start vào đường đi
        path.append(start)
    
    with open(output_file, 'w') as f:
        # Nếu không có phần tử nào trong stack path
        # thì in ra -1, nghĩa là không có đường đi
        if len(path) == 0:
            f.write(str(-1))
        else:
            # Đảo chiều của path rồi ghép thành chuỗi
            output_path = ' --> '.join([str(u) for u in reversed(path)])
            f.write(output_path)


# Hàm in ra console mảng trace
def show_trace():
    index_string = ' '.join(str(u).rjust(4) for u in range(1, vertex + 1))
    print(index_string)

    value_string = ' '.join(str(trace[u]).rjust(4) for u in range(1, vertex + 1))
    print(value_string)


if __name__ == '__main__':
    input_data()
    process()
    output()

    show_trace()
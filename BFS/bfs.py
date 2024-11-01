import os
import sys
import queue
from collections import deque

input_file = os.path.join(sys.path[0], 'bfs.inp')
output_file = os.path.join(sys.path[0], 'bfs.out')

# số đỉnh, số cạnh, đỉnh xuất phát, đỉnh đích
vertex, edge, start, finish = 0, 0, 0, 0

# danh sách kề
A = []

# mảng dùng để truy ngược, trace[u] = v nghĩa là trước đỉnh u là đỉnh v
trace = []

def input_data():
    with open(input_file) as f:
        global vertex, edge, start, finish        
        vertex, edge, start, finish = list(map(int, f.readline().split()))

        global A
        # Khởi tạo danh sách đỉnh kề
        A = [[] for _ in range(vertex + 1)]

        # Đọc từng dòng và nạp các đỉnh vào hàng A[u] tương ứng
        # Hàng A[u] chứa các đỉnh v kề với đỉnh u
        for _ in range(edge):
            u, v = map(int, f.readline().split())
            A[u].append(v)


def init():
    global trace
    
    # Khởi tạo mảng trace gồm toàn 0, nghĩa là tất cả đỉnh đều chưa có đỉnh liền trước
    trace = [0] * (vertex + 1)
    
    # Trước đỉnh start không có đỉnh nào  
    trace[start] = -1


def bfs():
    global start
    global A, trace

    # Khởi tạo hàng đợi q, nạp đỉnh start vào q
    q = queue.Queue()
    q.put(start)
    
    # current là biến tạm, chỉ đỉnh hiện hành
    current = 0
    
    # Trong khi hàng đợi q vẫn còn phần tử
    while q.empty() == False:
        # thì gán phần tử nằm ở đầu hàng đợi q vào biến tạm current và xóa luôn khỏi hàng đợi
        current = q.get()
        
        # Duyệt các đỉnh kề với đỉnh current
        for u in A[current]:
            # Nếu đỉnh u chưa ghé thăm thì đánh dấu ghé thăm u bằng mảng trace
            # rồi đẩy đỉnh u vào hàng đợi q
            if not trace[u]:
                trace[u] = current
                q.put(u)


def process():
    # Khởi tạo mảng trace
    init()

    # Thực hiện duyệt theo chiều rộng
    bfs()


def output():
    # Khai báo ngăn xếp path lưu các đỉnh của đường đi cần tìm
    path = deque()

    # Dùng tmp_finish để không làm mất giá trị của finish khi truy ngược
    tmp_finish = finish
    
    # Nếu có đường đi đến đỉnh finish thì mới thực hiện truy ngược trace
    if trace[tmp_finish]:
        # Dựa vào mảng trace, cho tmp_finish "lùi" dần về start
        while tmp_finish != start:
            # Trong khi chưa đụng đỉnh start, thì nạp đỉnh tmp_finish vào đường đi
            path.append(tmp_finish)
            
            # "Lùi" tmp_finish về đỉnh liền trước đó
            tmp_finish = trace[tmp_finish]
        
        # Nạp đỉnh start vào đường đi
        path.append(start)
    
    with open(output_file, 'w') as f:
        # Nếu không có phần tử nào trong ngăn xếp path
        # thì in ra -1, nghĩa là không có đường đi
        if len(path) == 0:
            f.write(str(-1))
        else:
            # Đảo chiều của path rồi ghép thành chuỗi
            output_path = ' --> '.join([str(u) for u in reversed(path)])
            f.write(output_path)


# Hàm in ra mảng trace
def show_trace():
    index_string = ' '.join(str(u).rjust(4) for u in range(1, vertex + 1))
    print(index_string)

    value_string = ' '.join(str(trace[u]).rjust(4) for u in range(1, vertex + 1))
    print(value_string)


if __name__ == '__main__':
    input_data()
    process()
    output()

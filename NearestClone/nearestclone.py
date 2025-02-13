import os
import sys
import queue

input_file = os.path.join(sys.path[0], 'nearestclone2.inp')
output_file = os.path.join(sys.path[0], 'nearestclone2.out')

node_number = 0
edge_number = 0

# Danh sách kề
A = []

# Mảng lưu màu của các đỉnh
colors = []
color_required = 0

# output
min_distance = sys.maxsize


def input_data():
    global node_number, edge_number, A, colors, color_required

    with open(input_file, 'r') as f:
        node_number, edge_number = map(int, f.readline().split())

        A = [[] for _ in range(node_number + 1)]

        for _ in range(edge_number):
            u, v = map(int, f.readline().split())
            A[u].append(v)
            A[v].append(u)

        colors = [0]
        colors.extend(list(map(int, f.readline().split())))
        color_required = int(f.readline())


def bfs(s, visited):
    global A, colors, color_required

    # Khai báo hàng đợi chứa các đỉnh kèm khoảng cách tính từ đỉnh s
    q = queue.Queue()  

    # Đẩy đỉnh s kèm khoảng cách (tính từ đỉnh s) vào hàng đợi
    q.put([s, 0])

    # Đánh dấu đỉnh s đã duyệt
    visited[s] = True

    # Đỉnh current và khoảng cách tính từ đỉnh s
    # current = []

    # Trong khi hàng đợi còn phần tử
    while q.empty() == False:
        # Lấy phần tử ở đầu hàng đợi
        current = q.get()

        # Duyệt từng đỉnh kề với đỉnh current
        for v in A[current[0]]:
            # Nếu đỉnh v chưa duyệt
            if visited[v] == False:
                # Kiểm tra có đúng màu yêu cầu không
                if colors[v] == color_required:
                    # Nếu đúng màu yêu cầu thì trả về khoảng cách (tính từ đỉnh s)
                    return current[1] + 1
                
                # Đánh dấu đã duyệt đỉnh v
                visited[v] = True

                # Nạp đỉnh và khoảng cách vào hàng đợi
                q.put([v, current[1] + 1])

    # Từ đỉnh s không loang đến được đỉnh nào cùng màu
    return sys.maxsize


def process():
    global node_number, min_distance

    # Khởi tạo giá trị false cho toàn mảng vst (visited)
    # vst = [False for _ in range(node_number + 1)]

    # Duyệt từng đỉnh bằng biến u
    for u in range(1, node_number + 1):
        # Nếu màu của đỉnh u đúng theo yêu cầu
        if colors[u] == color_required:
            # Thiết lập mảng visited về lại trạng thái ban đầu
            vst = [False for _ in range(node_number + 1)]

            # Thực hiện bfs() để loang đến đỉnh có cùng màu
            tmp_distance = bfs(u, vst)

            # Nếu có khoảng cách bằng 1
            if tmp_distance == 1:
                # thì output ngay kết quả
                min_distance = 1
                return

            # Ngược lại, ghi nhận khoảng cách nhỏ hơn
            min_distance = min(min_distance, tmp_distance)


def output():
    global min_distance

    with open(output_file, 'w') as f:
        if min_distance == sys.maxsize:
            f.write('-1')
        else:
            f.write(f'{min_distance}')


if __name__ == '__main__':
    input_data()
    process()
    output()
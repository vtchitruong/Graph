import os
import sys

input_file = os.path.join(sys.path[0], 'floyd-warshall.inp')
output_file = os.path.join(sys.path[0], 'floyd-warshall.out')

number_of_vertices = number_of_edges = start = finish = 0
graph = []

# Mảng trace dùng để lưu vết đường đi
# trace[u][v] = k nghĩa là: u -> k -> v
trace = []


def input_data():
    global number_of_vertices, number_of_edges, start, finish, graph

    with open(input_file, 'r') as f:
        number_of_vertices, number_of_edges, start, finish = map(int, f.readline().split())

        graph = [[float('inf') for _ in range(number_of_vertices + 1)] for _ in range(number_of_vertices + 1)]

        for u in range(1, number_of_vertices + 1):
            graph[u][u] = 0

        for _ in range(number_of_edges):
            u, v, w = map(int, f.readline().split())
            graph[u][v] = w


def floyd_warshall():
    global graph, trace, number_of_vertices

    # Khởi tạo mảng trace
    trace = [[-1 for _ in range(number_of_vertices + 1)] for _ in range(number_of_vertices + 1)]

    for u in range(1, number_of_vertices + 1):
        for v in range(1, number_of_vertices + 1):
            if graph[u][v] != float('inf') and u != v:
                trace[u][v] = u

    # Duyệt từng đỉnh trung gian k
    for k in range(1, number_of_vertices + 1):
        # Duyệt từng cặp đỉnh u, v
        for u in range(1, number_of_vertices + 1):
            for v in range(1, number_of_vertices + 1):
                # Nếu có thể đi u -> k và k -> v nhanh hơn so với u -> v
                if graph[u][k] + graph[k][v] < graph[u][v]:
                    # thi cập nhật lại khoảng cách u -> v
                    graph[u][v] = graph[u][k] + graph[k][v]

                    # Lưu vết đường đi u -> v thông qua k (u -> k -> v)
                    trace[u][v] = trace[k][v]


def output():
    global graph, trace, start, finish

    # Nếu không có đường đi từ đỉnh start đến đỉnh finish
    if graph[start][finish] == float('inf'):
        with open(output_file, 'w') as f:
            f.write('No path found')
            return

    # Ngược lại, có đường đi, thì dựa vào mảng trace để truy vết đường đi từ đỉnh finish về đỉnh start
    path = []

    # Biến tạm fn để lưu đỉnh hiện hành
    fn = finish

    # Trong khi fn chưa về đến đỉnh start
    while fn != start:
        # Thêm đỉnh fn vào đường đi
        path.append(fn)

        # Lùi về đỉnh trước đó
        fn = trace[start][fn]

    # Thêm đỉnh start vào đường đi
    path.append(start)

    with open(output_file, 'w') as f:
        # In ra khoảng cách ngắn nhất từ đỉnh start đến đỉnh finish
        f.write(f'{graph[start][finish]}\n')

        # In ra đường đi ngắn nhất từ đỉnh start đến đỉnh finish
        output_path = ' '.join(map(str, path[::-1]))
        f.write(f'{output_path}')


if __name__ == '__main__':
    input_data()
    floyd_warshall()
    output()

import os
import sys

input_file = os.path.join(sys.path[0], 'dijkstra.inp')
output_file = os.path.join(sys.path[0], 'dijkstra.out')

number_of_number_of_vertices, number_of_number_of_edges, start, finish = 0, 0, 0, 0

# Mảng D dùng để lưu khoảng cách ngắn nhất từ đỉnh start đến các đỉnh khác
# D[v] = d nghĩa là: khoảng cách ngắn nhất từ đỉnh start đến đỉnh v là d
D = []

# Mảng trace dùng để lưu vết đường đi
# trace[v] = u nghĩa là: u -> v
trace = []

INF = float('inf')

def input_data():
    global number_of_vertices, number_of_edges, start, finish, graph

    with open(input_file, 'r') as f:        
        number_of_vertices, number_of_edges, start, finish = list(map(int, f.readline().split()))

        graph = [[] for row in range(number_of_vertices + 1)]
        for i in range(number_of_edges):
            u, v, weight = list(map(int, f.readline().split()))
            graph[u].append((v, weight))


def dijkstra():
    global graph, D, trace
    
    # Khởi tạo mảng khoảng cách D
    D = [INF] * (number_of_vertices + 1)
    D[start] = 0;

    # Khởi tạo mảng trace
    trace = [-1] * (number_of_vertices + 1)

    # Biến q có kiểu list, mỗi phần tử là một tuple
    # với tuple[0] là khoảng cách d, tuple[1] là đỉnh v.
    # Nghĩa là, tại đỉnh v, khoảng cách ngắn nhất từ start đến đỉnh v là d.
    q = []
    q.append((0, start))

    # Trong khi q vẫn còn phần tử
    while q:
        # Lấy phần tử có giá trị D[u] nhỏ nhất
        min_element = min(q, key=lambda x: x[0])

        # Lấy ra đỉnh u có khoảng cách ngắn nhất từ start
        u = min_element[1]
        d_u = min_element[0]
        q.remove((d_u, u))

        # Dừng thuật toán khi đã đến đích
        if u == finish:
            break

        # Duyệt từng đỉnh v kề với đỉnh u
        for i in range(len(graph[u])):
            # v là đỉnh kề với u
            v = graph[u][i][0]

            # w là trọng số của cạnh u -> v
            w = graph[u][i][1]

            # Nếu có thể đi start -> u -> v nhanh hơn so với start -> v
            if D[u] + w < D[v]:
                # Nếu v đã có trong hàng đợi thì xoá phần tử liên quan
                if (D[v], v) in q:
                    q.remove((D[v], v))

                # Cập nhật lại khoảng cách ngắn nhất từ đỉnh start đến đỉnh v
                D[v] = D[u] + w
                
                # Lưu vết đường đi từ start đến v thông qua u
                trace[v] = u
                
                # Thêm vào q
                q.append((D[v], v))


def output():
    global D, trace, start, finish

    # Nếu không có đường đi từ đỉnh start đến đỉnh finish
    if D[finish] == INF:
        with open(output_file, 'w') as f:
            f.write('No path found')
        return

    # Ngược lại, có đuờng đi từ start đến finish, thì dựa vào mảng trace để truy vết đường đi
    path = list()
    
    # Biến tạm fn để lưu đỉnh hiện hành
    fn = finish

    # Trong khi fn chưa về đến đỉnh start
    while not fn == start:
        # Thêm đỉnh fn vào đường đi
        path.append(fn)

        # Lùi về đỉnh trước đó
        fn = trace[fn]
    
    # Thêm đỉnh start vào đường đi
    path.append(start)
    
    with open(output_file, 'w') as f:
        # In ra khoảng cách ngắn nhất từ đỉnh start đến đỉnh finish
        f.write(f'{D[finish]}\n')

        # In ra đường đi ngắn nhất từ đỉnh start đến đỉnh finish
        output_path = ' '.join([str(v) for v in reversed(path)])
        f.write(output_path)


if __name__ == '__main__':
    input_data()
    dijkstra()
    output()
    

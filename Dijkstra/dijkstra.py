import os
import sys

input_file = os.path.join(sys.path[0], 'dijkstra.inp')
output_file = os.path.join(sys.path[0], 'dijkstra.out')

# số đỉnh, số cạnh, đỉnh xuất phát, đỉnh đích
vertex, edge, start, finish = 0, 0, 0, 0

INF = float('inf')


def input_data():
    with open(input_file) as f:
        global vertices, edges, start, finish
        vertices, edges, start, finish = list(map(int, f.readline().split()))

        global graph
        graph = [[] for row in range(vertices + 1)]
        for i in range(edges):
            u, v, weight = list(map(int, f.readline().split()))
            graph[u].append((v, weight))


def init():    
    # d[v] là khoảng cách ngắn nhất từ start đến v
    global d # distance
    d = [INF for _ in range(vertices + 1)]
    d[start] = 0

    # trace[v] = u nghĩa là trước đỉnh v là đỉnh u
    global trace
    trace = [0 for _ in range(vertices + 1)]


def dijkstra():
    # Khai báo list q, mỗi phần tử là một tuple
    # với tuple[0] là khoảng cách d, tuple[1] là đỉnh v.
    # Nghĩa là, tại đỉnh v, khoảng cách ngắn nhất từ start đến v là d.
    q = []
    q.append((0, start))

    global graph, d
    while not len(q) == 0:
        # Xét đỉnh u của phần tử có d_u nhỏ nhất
        min_element = min(q, key=lambda x: x[0])
        u = min_element[1]
        d_u = min_element[0]
        q.remove((d_u, u))

        # Dừng thuật toán khi đã đến đích
        if u == finish:
            break

        # Duyệt các đỉnh kề với đỉnh u
        for i in range(len(graph[u])):
            v = graph[u][i][0]
            w = graph[u][i][1]

            if d[u] + w < d[v]:
                # Xóa phần tử có giá trị d[v] trong hàng đợi
                if (d[v], v) in q:
                    q.remove((d[v], v))

                # Lưu khoảng cách ngắn nhất mới
                d[v] = d[u] + w
                
                # Lưu vết
                trace[v] = u
                
                # Thêm vào hàng đợi
                q.append((d[v], v))


def output():
    
    path = list()
    global d
    if not d[finish] == INF:
        fn = finish # biến tạm

        # Dựa vào mảng trace, cho fn "lùi" dần về start
        while not fn == start:
            path.append(fn)
            fn = trace[fn]
        
        path.append(start)
    
    with open(output_file, 'w') as f:
        f.write(f'{d[finish]}\n')

        output_path = ' '.join([str(v) for v in reversed(path)])
        f.write(output_path)


if __name__ == '__main__':
    input_data()
    init()
    dijkstra()
    output()
    

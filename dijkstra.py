import xml.etree.ElementTree as ET
import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection
from typing import Dict, List, Tuple
import math
import heapq
import time

# Типы данных
Coord = Tuple[float, float]
EdgeItem = Tuple[Coord, Coord, str]
Graph = Dict[Coord, List[Tuple[Coord, float]]]

def haversine(coord1: Coord, coord2: Coord) -> float:
    lon1, lat1 = coord1
    lon2, lat2 = coord2
    R = 6371.0  # Радиус Земли в км
    phi1 = math.radians(lat1)
    phi2 = math.radians(lat2)
    dphi = math.radians(lat2 - lat1)
    dlambda = math.radians(lon2 - lon1)
    a = math.sin(dphi/2.0)**2 + math.cos(phi1) * math.cos(phi2) * math.sin(dlambda/2.0)**2
    return 2 * R * math.atan2(math.sqrt(a), math.sqrt(1 - a))

def dijkstra(graph: Graph, start: Coord, end: Coord, edges: List[EdgeItem]) -> Tuple[List[Coord], float, List[str]]:
    queue = [(0.0, start)]
    distances = {start: 0.0}
    previous = {start: None}
    street_names_dict = {node: None for node in graph}
    visited = set()

    while queue:
        current_distance, current_node = heapq.heappop(queue)
        if current_node in visited:
            continue
        visited.add(current_node)
        if current_node == end:
            break

        for neighbor, distance in graph.get(current_node, []):
            if neighbor not in visited:
                total_distance = current_distance + distance
                if neighbor not in distances or total_distance < distances[neighbor]:
                    distances[neighbor] = total_distance
                    previous[neighbor] = current_node
                    street_name = None
                    for edge in edges:
                        if (edge[0] == current_node and edge[1] == neighbor) or (edge[0] == neighbor and edge[1] == current_node):
                            street_name = edge[2]
                            break
                    street_names_dict[neighbor] = street_name
                    heapq.heappush(queue, (total_distance, neighbor))

    path = []
    street_names = []
    current_node = end
    while current_node is not None:
        path.append(current_node)
        if previous[current_node] is not None:
            street_name = street_names_dict[current_node]
            if street_name:
                street_names.append(street_name)
        current_node = previous[current_node]
    path.reverse()
    street_names.reverse()

    total_distance = distances.get(end, float('inf'))
    return path, total_distance, street_names

def build_graph(edges: List[EdgeItem]) -> Graph:
    graph = {}
    for start, end, _ in edges:
        dist = haversine(start, end)
        graph.setdefault(start, []).append((end, dist))
        graph.setdefault(end, []).append((start, dist))
    return graph

def read_graphml(file_path: str) -> Tuple[Dict[str, Coord], List[EdgeItem]]:
    nodes = {}
    edges = []
    try:
        tree = ET.parse(file_path)
        root = tree.getroot()
    except ET.ParseError as e:
        print(f"Ошибка парсинга файла: {e}")
        return nodes, edges

    ns = {'g': 'http://graphml.graphdrawing.org/xmlns'}
    for node in root.findall('.//g:node', ns):
        node_id = node.get('id')
        x, y = None, None
        for data in node.findall('.//g:data', ns):
            key = data.get('key')
            if key == 'd5':
                x = float(data.text)
            elif key == 'd4':
                y = float(data.text)
        if x is not None and y is not None:
            nodes[node_id] = (x, y)

    for edge in root.findall('.//g:edge', ns):
        source = edge.get('source')
        target = edge.get('target')
        if source not in nodes or target not in nodes:
            continue
        street_name = None
        for data in edge.findall('.//g:data', ns):
            if data.get('key') == 'd14':  # Используем d14 для имени улицы
                street_name = data.text if data.text else None
        edges.append((nodes[source], nodes[target], street_name))

    print(f"Прочитано узлов: {len(nodes)}, рёбер: {len(edges)}")
    # Выводим доступные улицы
    unique_streets = sorted(set(name for _, _, name in edges if name))
    print("Доступные улицы:", unique_streets)
    return nodes, edges

def find_street_index(edges: List[EdgeItem], street_name_query: str) -> Tuple[int, str]:
    for i, (_, _, name) in enumerate(edges):
        if name and name.lower() == street_name_query.lower():
            return i, name
    return -1, ""

def visualize_path_with_network(nodes: Dict[str, Coord], edges: List[EdgeItem], path: List[Coord], street_names: List[str], figsize: Tuple[int, int] = (15, 15)):
    plt.figure(figsize=figsize)
    ax = plt.gca()
    all_lines = [(start, end) for start, end, _ in edges]
    lc = LineCollection(all_lines, linewidths=0.3, colors='gray', alpha=0.4)
    ax.add_collection(lc)

    if path and len(path) > 1:
        path_lines = [(path[i], path[i+1]) for i in range(len(path)-1)]
        lc_path = LineCollection(path_lines, linewidths=2.0, colors='red', alpha=0.9)
        ax.add_collection(lc_path)
        for i in range(len(path)-1):
            if i < len(street_names) and street_names[i]:
                mid_point = ((path[i][0] + path[i+1][0]) / 2, (path[i][1] + path[i+1][1]) / 2)


    ax.autoscale()
    plt.axis('equal')
    plt.title('Кратчайший маршрут по Алматы')
    plt.xlabel('Долгота')
    plt.ylabel('Широта')
    plt.grid(False)
    plt.tight_layout()

def save_visualization(filename: str, dpi: int = 300) -> None:
    plt.savefig(filename, dpi=dpi, bbox_inches='tight')
    plt.close()

if __name__ == "__main__":
    nodes, edges = read_graphml("berlin_road_network.graphml")
    graph = build_graph(edges)

    # Три маршрута в Алматы с исправленными названиями
    routes = [
        ("100", "3"),
        ("70", "10"),
        ("80", "5")
    ]

    results = []
    for start_street, end_street in routes:
        start_index, start_name = find_street_index(edges, start_street)
        end_index, end_name = find_street_index(edges, end_street)
        if start_index == -1 or end_index == -1:
            print(f"Не удалось найти улицы: {start_street} или {end_street}")
            continue

        start_node = edges[start_index][0]
        end_node = edges[end_index][1]

        start_time = time.time()
        path, distance, street_names = dijkstra(graph, start_node, end_node, edges)
        duration = time.time() - start_time

        if not path:
            print(f"Путь от {start_street} до {end_street} не найден")
            continue

        print(f"\nМаршрут: {start_street} → {end_street}")
        print(f"Длина пути: {distance:.2f} км")
        print("Улицы:", ", ".join(filter(None, street_names)))
        print(f"Время выполнения: {duration:.3f} секунд")

        visualize_path_with_network(nodes, edges, path, street_names)
        filename = f"route_{start_street}_to_{end_street}.png".replace(" ", "_")
        save_visualization(filename)
        results.append((start_street, end_street, distance, filename, duration))

    # Таблица для отчёта
    print("\nТаблица результатов:")
    print("Пункт старта | Пункт назначения | Расстояние (км) | Рисунок | Время работы алгоритта")
    print("-------------|------------------|----------------|--------|----------------------")
    for start, end, dist, img, dur in results:
        print(f"{start} | {end} | {dist:.2f} | {img} | {dur:.3f} с")


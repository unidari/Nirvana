import osmnx as ox

# Загружаем дорожный граф для Алматы
G = ox.graph_from_place('Берлин, Германия', network_type='drive')
ox.save_graphml(G, 'berlin_road_network.graphml')
def floyd_warshall(graph, num_vertices):
    # Initialize distances with infinity
    distances = [[float('inf')] * num_vertices for _ in range(num_vertices)]

    # Set distances for edges in the graph
    for edge in graph:
        src, dest, weight = edge
        distances[src][dest] = weight
        distances[dest][src] = weight  # Since the graph is undirected

    # Update distances using Floyd-Warshall algorithm
    for k in range(num_vertices):
        for i in range(num_vertices):
            for j in range(num_vertices):
                distances[i][j] = min(distances[i][j], distances[i][k] + distances[k][j])

    return distances

def find_max_distance_pairs(distances):
    max_distance = 0
    max_distance_pairs = []

    num_vertices = len(distances)

    # Iterate through all pairs of vertices
    for i in range(num_vertices):
        for j in range(i+1, num_vertices):
            # If the distance is greater than the current maximum, update maximum
            if distances[i][j] > max_distance:
                max_distance = distances[i][j]
                max_distance_pairs = [(i, j)]
            # If the distance is equal to the current maximum, add the pair to the list
            elif distances[i][j] == max_distance:
                max_distance_pairs.append((i, j))

    return max_distance, max_distance_pairs

def main():
    # Read input from file
    with open('graph-large.txt', 'r') as file:
        num_vertices, num_edges = map(int, file.readline().split())
        graph = [list(map(int, line.split())) for line in file]

    # Apply Floyd-Warshall algorithm
    distances = floyd_warshall(graph, num_vertices)

    # Find pairs with maximum distance
    max_distance, max_distance_pairs = find_max_distance_pairs(distances)

    # Output the result
    print("Maximum distance:", max_distance)
    print("Pairs with maximum distance:")
    for pair in max_distance_pairs:
        print(pair)

if __name__ == "__main__":
    main()

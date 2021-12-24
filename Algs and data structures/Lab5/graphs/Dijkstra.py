from collections import defaultdict
from math import inf


class DijkstraAlgorithm:

    def __init__(self, graph, a, b, min_nodes=False):
        self.data = graph
        if len(self.data.edges) == 0:
            raise IndexError("Graph should have at least one edge!")
        if a not in self.data.nodes or b not in self.data.nodes:
            raise NameError("No such node in graph")
        if min_nodes:
            for edge in self.data.edges:
                edge[0] = 1
        self.list = self.__list_init__()
        self.path = []
        self.data.nodes.sort()
        self.nodes_count = len(self.data.nodes)
        self.__find_min_path__(a, b)
        self.draw_path()

    def __find_min_path__(self, start, end):
        distances = [inf for _ in range(self.nodes_count)]
        node_labels = [False for _ in range(self.nodes_count)]
        parents = [0 for _ in range(self.nodes_count)]
        distances[self.data.nodes.index(start)] = 0
        for i in range(self.nodes_count):
            new_node = - 1
            for j in range(self.nodes_count):
                if not node_labels[j] and (new_node == -1 or distances[j] < distances[new_node]):
                    new_node = j
            if distances[new_node] == inf:
                break
            node_labels[new_node] = True
            for item in self.list[self.data.nodes[new_node]]:
                to = item
                path_len = self.list[self.data.nodes[new_node]][item]
                if distances[new_node] + path_len < distances[self.data.nodes.index(to)]:
                    distances[self.data.nodes.index(to)] = distances[new_node] + path_len
                    parents[self.data.nodes.index(to)] = new_node

        end_id = self.data.nodes.index(end)
        start_id = self.data.nodes.index(start)
        while start_id != end_id:
            end_id = parents[end_id]
            self.path.append(self.data.nodes[end_id])
        self.path.reverse()
        self.path.append(end)

    def __list_init__(self):
        adj_list = defaultdict(lambda: defaultdict(lambda: 0))
        for weight, start, end in self.data.edges:
            adj_list[start][end] = weight
            adj_list[end][start] = weight
        return adj_list

    def draw_path(self):
        self.data.visual.highlight_path(self.path)

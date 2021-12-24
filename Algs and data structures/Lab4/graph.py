import matplotlib.pyplot as plt
import networkx as nx
from math import inf


class GraphVisualization:

    def __init__(self):
        self.graph = nx.Graph()
        self.positions = []

    def add_vertex(self, a):
        self.graph.add_node(a)

    def add_edge(self, a, b, weight):
        self.graph.add_edge(a, b, weight=weight)

    def visualize(self, filename):
        nx.draw_networkx(self.graph)
        plt.savefig(filename + ".png")
        plt.close()


class Graph:

    def __init__(self):
        self.nodes = []
        self.edges = []
        self.visual = GraphVisualization()

    def add_vertex(self, name):
        if name not in self.nodes:
            self.nodes.append(name)

    def add_edge(self, first, second, weight):
        temp = [weight, first, second]
        if temp not in self.edges:
            self.edges.append(temp)
            self.visual.add_edge(first, second, weight)
            self.add_vertex(first)
            self.add_vertex(second)
        else:
            raise NameError("Edge already in graph!")

    def show_graph(self):
        self.visual.visualize("graph")

    def string_ribs(self):
        result = ""
        for edge in self.edges:
            result += "{} <==> {}, weight: {}\n".format(str(edge[1]), str(edge[2]), str(edge[0]))
        return result


class KruskalAlgorithm:

    def __init__(self, graph):
        self.net_tree = Graph()
        self.data = graph
        if len(self.data.edges) == 0:
            raise IndexError("Graph should have at least one edge!")
        self.__create_tree__()

    def __create_tree__(self):
        nodes = Set()
        edges = sorted(self.data.edges, key=lambda key: key[0])
        for item in self.data.nodes:
            nodes.add_item(item)
        for edge in edges:
            if nodes.issubset(edge[1]) and nodes.issubset(edge[2]):
                if nodes.not_in_one_subset(edge[1], edge[2]):
                    self.net_tree.add_edge(edge[1], edge[2], edge[0])
                    nodes.merge(edge[1], edge[2])

    def show_tree(self):
        self.net_tree.visual.visualize("net_tree")


class PrimAlgorithm:

    def __init__(self, graph):
        self.net_tree = Graph()
        self.data = graph
        if len(self.data.edges) == 0:
            raise IndexError("Graph should have at least one edge!")
        self.data.nodes.sort()
        self.matrix = self.__matrix_init__()
        self.nodes_count = len(self.data.nodes)
        self.used_nodes = [0 * i for i in range(self.nodes_count)]
        self.__create_tree__()

    def __create_tree__(self):
        edges_count = 0
        self.used_nodes[0] = True
        while edges_count < self.nodes_count - 1:
            new_edge = self.__find_min_edge__()
            self.net_tree.add_edge(new_edge[0], new_edge[1], new_edge[2])
            edges_count += 1

    def __find_min_edge__(self):
        minimum = inf
        start_id = 0
        end_id = 0
        for i in range(self.nodes_count):
            if self.used_nodes[i]:
                for j in range(self.nodes_count):
                    if not self.used_nodes[j] and self.matrix[i][j]:
                        if self.matrix[i][j] < minimum:
                            minimum = self.matrix[i][j]
                            start_id = i
                            end_id = j
        self.used_nodes[end_id] = True
        return [self.data.nodes[start_id], self.data.nodes[end_id], self.matrix[start_id][end_id]]

    def __matrix_init__(self):
        size = len(self.data.nodes)
        matrix = [[0.0] * size for i in range(size)]
        for i in range(size):
            for j in range(size):
                path_exists, edge = self.__path_exists__(self.data.nodes[i], self.data.nodes[j])
                if path_exists:
                    matrix[i][j] = edge[0]
                else:
                    matrix[i][j] = 0
        return matrix

    def __path_exists__(self, node1, node2):
        for edge in self.data.edges:
            if (node1 == edge[1] and node2 == edge[2]) or (node2 == edge[1] and node1 == edge[2]):
                return True, edge
        return False, None

    def show_tree(self):
        self.net_tree.visual.visualize("net_tree")


class Set:

    def __init__(self):
        self.data = []

    def add_item(self, item):
        if item not in self.data:
            self.data.append(str(item))

    def issubset(self, sub):
        if sub in self.data:
            return True, self.data.index(sub)
        for item in self.data:
            id = item.find(sub)
            if id != -1:
                return True, self.__getindex__(self.data, sub)
        return False

    def not_in_one_subset(self, item1, item2):
        first = self.issubset(item1)
        second = self.issubset(item2)
        if first and second:
            if first[1] != second[1]:
                return True, first[1], second[1]
            return False

    def __getindex__(self, list_of_strings, substring):
        try:
            return next(i for i, e in enumerate(list_of_strings) if substring in e)
        except StopIteration:
            raise NameError("No such element")

    def merge(self, item1, item2):
        new_item = ""
        if self.issubset(item1) and self.issubset(item2) and len(self.data) != 1:
            try:
                id1 = self.__getindex__(self.data, item1)
                new_item += self.data[id1]
                self.data.remove(self.data[id1])
            except NameError:
                raise NameError("Error in merging elements")
            try:
                id2 = self.__getindex__(self.data, item2)
                new_item += self.data[id2]
                self.data.remove(self.data[id2])
                self.data.append(new_item)
            except NameError:
                raise NameError("Error in merging elements")



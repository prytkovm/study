from math import inf
from collections import defaultdict


class Floyd:

    def __init__(self, graph, start, end):
        self.data = graph
        if len(self.data.edges) == 0:
            raise IndexError("Graph must have at least one edge!")
        if start not in self.data.nodes or end not in self.data.nodes:
            raise NameError("No such node in graph!")
        self.data.nodes.sort()
        self.matrix, self.next_node = self.__matrix_init__()
        try:
            self.__find_path__(start, end)
        except NameError as e:
            raise NameError(str(e))

    def __find_path__(self, start, end):
        for i in self.data.nodes:
            for j in self.data.nodes:
                for k in self.data.nodes:
                    if self.matrix[j][k] > self.matrix[j][i] + self.matrix[i][k]:
                        self.matrix[j][k] = self.matrix[j][i] + self.matrix[i][k]
                        self.next_node[j][k] = self.next_node[j][i]
        try:
            self.__restore__path__(start, end)
        except NameError as e:
            raise NameError(str(e))

    def __restore__path__(self, start, end):
        path = [start]
        if self.matrix[start][end] == inf:
            raise NameError("No path!")
        while start != end:
            start = self.next_node[start][end]
            path.append(start)
        self.draw_path(path)
        return path

    def __matrix_init__(self):
        matrix = defaultdict(lambda: defaultdict(lambda: inf))
        parents = defaultdict(lambda: defaultdict(lambda: 0))
        for weight, start, end in self.data.edges:
            matrix[start][end] = weight
            parents[start][end] = end
        for node in self.data.nodes:
            matrix[node][node] = inf
            parents[node][node] = node
        return matrix, parents

    def draw_path(self, path):
        self.data.visual.highlight_path(path)

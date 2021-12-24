import math
from math import inf


class SolveTSP:

    def __init__(self, graph):
        self.data = graph
        if len(self.data.nodes) == 0:
            raise IndexError("At least one node should be in graph")
        self.data.nodes.sort()
        self.matrix = self.__matrix_init__()
        self.final_path = [None] * (len(self.matrix) + 1)
        self.final_cost = inf
        try:
            path = self.__TSP__()
            self.data.visual.highlight_path(path)
        except IndexError as e:
            raise IndexError(str(e))

    def __TSP__(self):
        size = len(self.matrix)
        curr_bound = 0
        curr_path = [-1] * (size + 1)
        visited = [False] * size
        for i in range(size):
            curr_bound += self.__first_min__(i) + self.__second_min__(i)
        curr_bound = math.ceil(curr_bound / 2)
        visited[0] = True
        curr_path[0] = 0
        self.__TSP_record__(curr_bound, 0, 1, curr_path, visited)
        if self.final_path == [None] * (len(self.matrix) + 1):
            raise IndexError("No path exists!")
        path = self.__indexes_to_nodes__(self.final_path)
        return path

    def __TSP_record__(self, curr_bound, curr_weight, level, curr_path, visited):
        size = len(self.matrix)
        if level == size:
            if self.matrix[curr_path[level - 1]][curr_path[0]] != 0:
                curr_res = curr_weight + self.matrix[curr_path[level - 1]][curr_path[0]]
                if curr_res < self.final_cost:
                    self.__init_final_path__(curr_path)
                    self.final_cost = curr_res
            return
        for i in range(size):
            if self.matrix[curr_path[level - 1]][i] != 0 and not visited[i]:
                temp = curr_bound
                curr_weight += self.matrix[curr_path[level - 1]][i]
                if level == 1:
                    curr_bound -= (self.__first_min__(curr_path[level - 1]) + self.__first_min__(i)) / 2
                else:
                    curr_bound -= (self.__second_min__(curr_path[level - 1]) + self.__first_min__(i)) / 2
                if curr_bound + curr_weight < self.final_cost:
                    curr_path[level] = i
                    visited[i] = True
                    self.__TSP_record__(curr_bound, curr_weight, level + 1, curr_path, visited)
                curr_weight -= self.matrix[curr_path[level - 1]][i]
                curr_bound = temp
                visited = [False] * len(visited)
                for j in range(level):
                    if curr_path[j] != -1:
                        visited[curr_path[j]] = True

    def __init_final_path__(self, curr_path):
        self.final_path[:len(self.matrix) + 1] = curr_path[:]
        self.final_path[len(self.matrix)] = curr_path[0]

    def __first_min__(self, i):
        min = inf
        size = len(self.matrix)
        for k in range(size):
            if self.matrix[i][k] < min and i != k:
                min = self.matrix[i][k]
        return min

    def __second_min__(self, i):
        first, second = inf, inf
        size = len(self.matrix)
        for j in range(size):
            if i == j:
                continue
            if self.matrix[i][j] <= first:
                second = first
                first = self.matrix[i][j]
            elif self.matrix[i][j] <= second and self.matrix[i][j] != first:
                second = self.matrix[i][j]
        return second

    def __matrix_init__(self):
        size = len(self.data.nodes)
        matrix = [[0.0] * size for _ in range(size)]
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
            if (node1 == edge[1] and node2 == edge[2]) or (node1 == edge[2] and node2 == edge[1]):
                return True, edge
        return False, None

    def __indexes_to_nodes__(self, indexes):
        nodes = []
        for id in indexes:
            nodes.append(self.data.nodes[id])
        return nodes

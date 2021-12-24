from copy import copy
import random


class NodesColouring:

    def __init__(self, graph):
        self.data = graph
        self.data.nodes = self.__sort_nodes__()
        self.color_queue = copy(self.data.nodes)
        self.used_colors = []
        self.__paint__()

    def __paint__(self):
        while len(self.color_queue) != 0:
            new_node_color = self.__generate_color__()
            new_set = self.__get_independent_set__(self.color_queue[0])
            self.data.visual.add_new_color_to_group(new_set, new_node_color)
        self.data.visual.highlight_nodes()

    def __generate_color__(self):
        color = "#" + ''.join([random.choice('0123456789ABCDEF') for _ in range(6)])
        while color in self.used_colors:
            color = "#" + ''.join([random.choice('0123456789ABCDEF') for _ in range(6)])
        self.used_colors.append(color)
        return color

    def __sort_nodes__(self):
        temp = []
        node_pow = 0
        for node in self.data.nodes:
            for edge in self.data.edges:
                if node in edge:
                    node_pow += 1
            temp.append([node, node_pow])
            node_pow = 0
        temp.sort(key=lambda x: x[1], reverse=True)
        sorted_nodes = [name[0] for name in temp]
        return sorted_nodes

    def __get_independent_set__(self, node):
        result = []
        for _, item in enumerate(self.color_queue[:]):
            res, _ = self.__path_exists__(node, item)
            if not res:
                allow_coloring = True
                if len(result) != 0:
                    for i in range(len(result)):
                        exists, _ = self.__path_exists__(result[i], item)
                        if exists:
                            allow_coloring = False
                            break
                if allow_coloring:
                    result.append(item)
                    self.color_queue.remove(item)
        return result

    def __path_exists__(self, node1, node2):
        for edge in self.data.edges:
            if (node1 == edge[1] and node2 == edge[2]) or (node2 == edge[1] and node1 == edge[2]):
                return True, edge
        return False, None

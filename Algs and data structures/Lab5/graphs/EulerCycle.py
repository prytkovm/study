from collections import defaultdict
import networkx as nx
import matplotlib.pyplot as plt


class GraphVisualization:

    def __init__(self):
        self.graph = nx.Graph()
        self.nodes_pack = []

    def add_vertex(self, a):
        self.graph.add_node(a)

    def add_edge(self, a, b, weight):
        self.graph.add_edge(a, b, weight=weight)

    def visualize(self, filename):
        nx.draw_networkx(self.graph)
        plt.savefig(filename + ".png")
        plt.close()
        # plt.show()

    def highlight_path(self, points):
        pos = nx.spring_layout(self.graph)
        nx.draw(self.graph, pos)
        path_edges = list(zip(points, points[1:]))
        nx.draw_networkx_nodes(self.graph, pos, nodelist=points)
        nx.draw_networkx_labels(self.graph, pos)
        nx.draw_networkx_edges(self.graph, pos, edgelist=path_edges, edge_color='red', width=3, arrows=True)
        nx.draw_networkx_nodes(self.graph, pos, nodelist=[points[0]], node_color='red')
        plt.savefig("graph.png")
        plt.close()
        # plt.show()

    def add_new_color_to_group(self, group, color):
        self.nodes_pack.append(dict(color=color, nodes=group))

    def highlight_nodes(self):
        pos = nx.spring_layout(self.graph)
        nx.draw(self.graph, pos)
        for item in self.nodes_pack:
            nx.draw_networkx_nodes(self.graph, pos, nodelist=item["nodes"], node_color=item["color"])
        nx.draw_networkx_labels(self.graph, pos)
        nx.draw_networkx_edges(self.graph, pos, edgelist=self.graph.edges)
        plt.savefig("graph.png")
        plt.show()


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


class FindEulerPath:

    def __init__(self, graph):
        self.data = graph
        self.adj_list = self.__adj_list_init__()
        self.euler_path = []
        self.visited = [False] * len(self.data.edges)
        self.first = dict.fromkeys(self.data.nodes, 0)
        self.__find_euler_path__(self.data.nodes[0])
        if len(self.euler_path) != 0:
            self.euler_path.append(self.euler_path[0])
        else:
            raise IndexError("No Euler path in this graph")
        self.data.visual.highlight_path(self.euler_path)

    def __find_euler_path__(self, u):
        while self.first[u] < len(self.adj_list[u]):
            data = self.adj_list[u][self.first[u]]
            v = data[1]
            i = data[0]
            self.first[u] += 1
            if not self.visited[i]:
                self.visited[i] = True
                self.__find_euler_path__(v)
                self.euler_path.append(v)

    def __adj_list_init__(self):
        adj_list = defaultdict(lambda: [])
        for item in self.data.nodes:
            for edge in self.data.edges:
                if item in edge:
                    rib_id = self.data.edges.index(edge)
                    if item == edge[1]:
                        adj_list[item].append([rib_id, edge[2]])
                    else:
                        adj_list[item].append([rib_id, edge[1]])
        return adj_list

    def path_to_string(self):
        result = ""
        for item in self.euler_path:
            result += item + "--"
        return result

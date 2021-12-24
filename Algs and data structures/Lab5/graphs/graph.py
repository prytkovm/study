import matplotlib.pyplot as plt
import networkx as nx


class GraphVisualization:

    def __init__(self):
        self.graph = nx.Graph()
        self.positions = []
        self.nodes_pack = []

    def add_vertex(self, a):
        self.graph.add_node(a)

    def add_edge(self, a, b, weight):
        self.graph.add_edge(a, b, weight=weight)

    def visualize(self, filename):
        nx.draw_networkx(self.graph)
        plt.savefig(filename + ".png")
        plt.close()

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
        plt.close()

    def delete_edge(self, edge):
        self.graph.remove_edge(edge[0], edge[1])
        self.graph.remove_node(edge[0])
        self.graph.remove_node(edge[1])


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
            self.show_graph()
        else:
            raise NameError("Edge already in graph!")

    def show_graph(self):
        self.visual.visualize("graph")

    def string_ribs(self):
        result = ""
        for edge in self.edges:
            result += "{} <==> {}, weight: {}\n".format(str(edge[1]), str(edge[2]), str(edge[0]))
        return result

    def delete_edge(self, edge):
        flag = False
        for e in self.edges:
            if (e[1] == edge[0] and e[2] == edge[1]) or (e[1] == edge[1] and e[2] == edge[0]):
                flag = True
                self.edges.remove(e)
                self.nodes.remove(edge[0])
                self.nodes.remove(edge[1])
                try:
                    self.visual.delete_edge(edge)
                except NameError as e:
                    raise NameError(str(e))
        if not flag:
            raise NameError("No such edge in graph!")

    def clear_graph(self):
        for edge in self.edges:
            self.edges.remove(edge)
            self.visual.delete_edge(edge[1:2])


class DiGraphVisualization:

    def __init__(self):
        self.graph = nx.DiGraph()
        self.positions = []
        self.colors = []

    def add_vertex(self, a):
        self.graph.add_node(a)

    def add_edge(self, a, b, weight):
        self.graph.add_edge(a, b, weight=abs(weight))

    def visualize(self, filename):
        nx.draw_networkx(self.graph)
        plt.savefig(filename + ".png")
        plt.close()

    def highlight_path(self, points):
        pos = nx.spring_layout(self.graph)
        nx.draw(self.graph, pos)
        path_edges = list(zip(points, points[1:]))
        nx.draw_networkx_nodes(self.graph, pos, nodelist=points)
        nx.draw_networkx_labels(self.graph, pos)
        nx.draw_networkx_edges(self.graph, pos, edgelist=path_edges, edge_color='r', width=3)
        plt.savefig("graph.png")
        plt.close()

    def delete_edge(self, edge):
        self.graph.remove_edge(edge[0], edge[1])
        self.graph.remove_node(edge[0])
        self.graph.remove_node(edge[1])


class DirectedGraph:

    def __init__(self):
        self.nodes = []
        self.edges = []
        self.visual = DiGraphVisualization()

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
            self.show_graph()
        else:
            raise NameError("Edge already in graph!")

    def show_graph(self):
        self.visual.visualize("graph")

    def string_ribs(self):
        result = ""
        for edge in self.edges:
            result += "{} ==> {}, weight: {}\n".format(str(edge[1]), str(edge[2]), str(edge[0]))
        return result

    def delete_edge(self, edge):
        flag = False
        for e in self.edges:
            if e[1] == edge[0] and e[2] == edge[1]:
                flag = True
                self.edges.remove(e)
                self.nodes.remove(edge[0])
                self.nodes.remove(edge[1])
                try:
                    self.visual.delete_edge(edge)
                except NameError as e:
                    raise NameError(str(e))
        if not flag:
            raise NameError("No such edge in graph, maybe wrong direction ?")

    def clear_graph(self):
        for edge in self.edges:
            self.edges.remove(edge)
            self.visual.delete_edge(edge[1:2])
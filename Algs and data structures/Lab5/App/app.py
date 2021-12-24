import sys
from UI import *
from PyQt6 import QtWidgets, QtGui
from PyQt6.QtWidgets import QMessageBox
from graphs import *
from App.Files import FileProcess


class Application:

    def __init__(self):
        self.app = QtWidgets.QApplication(sys.argv)
        self.MainWindow = QtWidgets.QMainWindow()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self.MainWindow)
        self.ui.go.clicked.connect(self.run_algo)
        self.ui.AddEdge.clicked.connect(self.add_edge)
        self.ui.DeleteEdge.clicked.connect(self.delete_edge)
        self.ui.actionOpen_graph.triggered.connect(self.read_graph_from_file)
        self.ui.actionSave_graph.triggered.connect(self.write_graph_to_file)
        self.graph = Graph()
        self.di_graph = DirectedGraph()
        self.graphScene = QtWidgets.QGraphicsScene()
        self.alert = QMessageBox()
        self.alert.setIcon(QMessageBox.Icon.Critical)
        self.MainWindow.show()
        self.app.exec()

    def add_edge(self):
        try:
            if len(self.ui.StartNodeName.text()) == 0 or len(self.ui.EndNodeName.text()) == 0 or len(
                    self.ui.EdgeWeight.text()) == 0:
                self.alert.setText("You must fill all node information!")
                self.alert.exec()
                return
            if not self.ui.TSP.isChecked() and \
                    not self.ui.MinNodesPath.isChecked() and \
                    not self.ui.EulerPath.isChecked() and \
                    not self.ui.NodesColoring.isChecked() and \
                    not self.ui.Dijkstra.isChecked() and \
                    not self.ui.DP.isChecked():
                self.alert.setText("Please, specify algo first to let us know graph type")
                self.alert.exec()
                return
            if not self.ui.DP.isChecked():
                self.graph.add_edge(str(self.ui.StartNodeName.text()), str(self.ui.EndNodeName.text()),
                                    int(self.ui.EdgeWeight.text()))
                # self.update_scene()
            else:
                # self.graph.clear_graph()
                self.di_graph.add_edge(str(self.ui.StartNodeName.text()), str(self.ui.EndNodeName.text()),
                                       int(self.ui.EdgeWeight.text()))
            self.update_scene()
        except NameError as e:
            self.alert.setText(str(e))
            self.alert.exec()
            return

    def delete_edge(self):
        start = self.ui.DelStartName.text()
        end = self.ui.DelEndName.text()
        if len(self.graph.edges) != 0:
            try:
                self.graph.delete_edge([start, end])
                self.graph.show_graph()
                self.update_scene()
            except NameError as e:
                self.alert.setText(str(e))
                self.alert.exec()
                return
        elif len(self.di_graph.edges) != 0:
            try:
                self.di_graph.delete_edge([start, end])
                self.di_graph.show_graph()
                self.update_scene()
            except NameError as e:
                self.alert.setText(str(e))
                self.alert.exec()
                return
        else:
            self.alert.setText("Your graph is empty!")
            self.alert.exec()
            return

    def run_algo(self):
        start_node_dialog = InputDialog("start node")
        end_node_dialog = InputDialog("end node")
        if self.ui.Dijkstra.isChecked():
            start = start_node_dialog.showDialog()
            end = end_node_dialog.showDialog()
            try:
                DijkstraAlgorithm(self.graph, start, end)
                self.update_scene()
            except IndexError as e:
                self.alert.setText(str(e))
                self.alert.exec()
                return
            except NameError as e:
                self.alert.setText(str(e))
                self.alert.exec()
                return
        elif self.ui.DP.isChecked():
            start = start_node_dialog.showDialog()
            end = end_node_dialog.showDialog()
            try:
                Floyd(self.di_graph, start, end)
                self.update_scene()
            except IndexError as e:
                self.alert.setText(str(e) + "Note: DP algo needs directed graph")
                self.alert.exec()
                return
            except NameError as e:
                self.alert.setText(str(e) + "Note: DP algo needs directed graph")
                self.alert.exec()
                return
        elif self.ui.NodesColoring.isChecked():
            NodesColouring(self.graph)
            self.update_scene()
        elif self.ui.EulerPath.isChecked():
            try:
                FindEulerPath(self.graph)
                self.update_scene()
            except IndexError as e:
                self.alert.setText(str(e))
                self.alert.exec()
                return
        elif self.ui.TSP.isChecked():
            try:
                SolveTSP(self.graph)
                self.update_scene()
            except IndexError as e:
                self.alert.setText(str(e))
                self.alert.exec()
                return
        elif self.ui.MinNodesPath.isChecked():
            start = start_node_dialog.showDialog()
            end = end_node_dialog.showDialog()
            try:
                DijkstraAlgorithm(self.graph, start, end, min_nodes=True)
                self.update_scene()
            except IndexError as e:
                self.alert.setText(str(e))
                self.alert.exec()
                return
            except NameError as e:
                self.alert.setText(str(e))
                self.alert.exec()
                return
        else:
            self.alert.setText("You should choose algo first!")
            self.alert.exec()
            return

    def update_scene(self):
        pix = QtGui.QPixmap("graph.png")
        item = QtWidgets.QGraphicsPixmapItem(pix)
        self.graphScene.clear()
        self.graphScene.addItem(item)
        self.ui.graphView.setScene(self.graphScene)
        self.update_edges()

    def update_edges(self):
        if len(self.graph.edges) != 0:
            edges = self.graph.string_ribs()
            self.ui.edgesView.clear()
            self.ui.edgesView.setText(edges)
        elif len(self.di_graph.edges) != 0:
            edges = self.di_graph.string_ribs()
            self.ui.edgesView.clear()
            self.ui.edgesView.setText(edges)

    def write_graph_to_file(self):
        FD = FileDialog()
        path = FD.showWriteDialog()
        if len(self.graph.nodes) != 0:
            try:
                FileProcess.write(path, self.graph.edges)
            except FileNotFoundError as e:
                self.alert.setText(str(e))
                self.alert.exec()
                return
        elif len(self.di_graph.nodes) != 0:
            try:
                FileProcess.write(path, self.di_graph.edges)
            except FileNotFoundError as e:
                self.alert.setText(str(e))
                self.alert.exec()
                return
        else:
            self.alert.setText("Your graph is empty!")
            self.alert.exec()
            return

    def read_graph_from_file(self):
        self.graph = Graph()
        self.di_graph = DirectedGraph()
        FD = FileDialog()
        path = FD.showDialog()
        data = FileProcess.read(path)
        data = list(data)
        ID = InputDialog("Enter type of yor graph[d/u]")
        result = ID.showDialog()
        if result == "d":
            for item in data:
                self.di_graph.add_edge(item[0], item[1], int(item[2]))
            self.di_graph.show_graph()
        elif result == "u":
            for item in data:
                self.graph.add_edge(item[0], item[1], int(item[2]))
            self.graph.show_graph()
        else:
            self.alert.setText("Unknown type!")
            self.alert.exec()
            return
        self.update_scene()

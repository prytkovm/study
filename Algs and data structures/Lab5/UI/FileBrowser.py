from PyQt6.QtWidgets import QMainWindow, QFileDialog


class FileDialog(QMainWindow):

    def __init__(self):
        super().__init__()

    def showDialog(self):
        filename = QFileDialog.getOpenFileName(self, 'Open file', '')[0]
        return filename

    def showWriteDialog(self):
        filename = QFileDialog.getSaveFileName(self, 'Save file', '.txt')[0]
        return filename

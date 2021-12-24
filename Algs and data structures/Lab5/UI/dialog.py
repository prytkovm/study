from PyQt6.QtWidgets import QWidget, QPushButton, QInputDialog, QMessageBox, QDialog


class InputDialog(QWidget):

    def __init__(self, txt):
        super().__init__()
        self.text = txt

    def showDialog(self):
        alert = QMessageBox()
        alert.setIcon(QMessageBox.Icon.Critical)
        text, ok = QInputDialog.getText(self, 'Input Dialog',
                                        f'Enter {self.text}:')
        if len(text) == 0:
            alert.setText("Input shouldn't be zero-length!")
            alert.exec()
            self.showDialog()
        if ok:
            return text

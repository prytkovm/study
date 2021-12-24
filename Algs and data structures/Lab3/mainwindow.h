#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCheckBox>
#include <QIntValidator>
#include <trees.cpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    Tree *newTree;
    AVL_tree *newAVL;
private slots:
    void on_genButton_clicked();
    void on_outButton_clicked();
    void on_saveButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

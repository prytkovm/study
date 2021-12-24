#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIntValidator>
#include <QMessageBox>
#include "search.cpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    BinarySearch *newSearch;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_generateSet_button_clicked();
    void on_searchButton_clicked();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "text_search.cpp"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Text search"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_searchButton_clicked()
{
    QMessageBox allert;
    QTextCursor cursor(ui->userText->document());
    QTextCharFormat fmt = cursor.charFormat();
    fmt.setBackground (Qt::transparent);
    cursor.setPosition(0, QTextCursor::MoveAnchor);
    cursor.setPosition(ui->userText->toPlainText().length(), QTextCursor::KeepAnchor);
    cursor.setCharFormat(fmt);
    int res = 0;
    TextSearch newTextSearch(ui->userText->toPlainText().toStdString());
    if (ui->userText->toPlainText().length() < ui->searchText->toPlainText().length() || ui->userText->toPlainText() == "" || ui->searchText->toPlainText() == "")
    {
        allert.setIcon(QMessageBox::Warning);
        allert.setText("Incorrect search key or text!");
        allert.exec();
        return;
    }
    if (ui->searchKMP->isChecked())
        res = newTextSearch.search_KMP((ui->searchText->toPlainText().toStdString()));
    else if (ui->searchBM->isChecked())
        res = newTextSearch.search_BM((ui->searchText->toPlainText().toStdString()));
    else if (ui->searchRab->isChecked())
        res = newTextSearch.search_Rab((ui->searchText->toPlainText().toStdString()));
    else
    {
        allert.setIcon(QMessageBox::Warning);
        allert.setText("You must choose searching algorithm before search!");
        allert.exec();
        return;
    }
    if (res != -1)
    {
        fmt.setBackground(Qt::yellow);
        cursor.setPosition(res, QTextCursor::MoveAnchor);
        cursor.setPosition(res + ui->searchText->toPlainText().length(), QTextCursor::KeepAnchor);
        cursor.setCharFormat(fmt);
    }
    else
    {
        allert.setIcon(QMessageBox::Information);
        allert.setText("No results with this key");
        allert.exec();
        return;
    }
}

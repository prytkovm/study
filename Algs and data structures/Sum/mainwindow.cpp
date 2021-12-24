#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    newSummator = new Summator;
    setWindowTitle(tr("Sum"));
    ui->sumId->setValidator(new QIntValidator(0, 10000, this));
    ui->sumResult->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete newSummator;
    delete ui;
}


void MainWindow::on_sumButton_clicked()
{
    QMessageBox allert;
    int id;
    long long x = 0;
    allert.setIcon(QMessageBox::Warning);
    if (ui->sumId->text() == "")
    {
        allert.setText("You must enter id!");
        allert.exec();
        return;
    }
    id = ui->sumId->text().toInt();
    ui->sumResult->clear();
    if (ui->iterativeSum->isChecked())
    {
        ui->sumResult->append(QString::number(newSummator->iterative_sum(id)));
    }
    else if (ui->recurciveSum->isChecked())
    {
        newSummator->recursive_sum(x, id);
        ui->sumResult->append(QString::number(x));
    }
    else
    {
        allert.setText("You must choose sum algorithm!");
        allert.exec();
        return;
    }
}


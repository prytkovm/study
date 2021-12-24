#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sorting.cpp"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->minValue->setMinimum(INT_MIN);
    ui->minValue->setMaximum(INT_MAX);
    ui->maxValue->setMinimum(INT_MIN);
    ui->maxValue->setMaximum(INT_MAX);
    ui->sortTime->setDecMode();
    setWindowTitle(tr("Lab 1"));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_genButton_clicked()
{
    int min, max;
    int array_length;
    QMessageBox allert;
    allert.setIcon(QMessageBox::Warning);
    if (ui->radioButton->isChecked())
        array_length = 1000;
    else if (ui->radioButton_2->isChecked())
        array_length = 4000;
    else if (ui->radioButton_3->isChecked())
        array_length = 6000;
    else
    {
        allert.setText("Необходимо выбрать длину массива!");
        allert.exec();
        return;
    }
    min = ui->minValue->value();
    max = ui->maxValue->value();
    if (min > max)
    {
        allert.setText("Нижняя граница не может быть больше верхней!");
        allert.exec();
        return;
    }
    Array newArray(array_length);
    newArray.generate_array(min, max);
    ui->originalArray->clear();
    for (int i = 0; i < array_length; i++)
        ui->originalArray->append(QString::number(newArray.array[i]));
    ui->sortedArray->clear();
    newArray.sort(newArray.array);
    for (int i = 0; i < array_length; i++)
        ui->sortedArray->append(QString::number(newArray.array[i]));
    ui->sortTime->display(QString::number(newArray.get_sortTime()));
}

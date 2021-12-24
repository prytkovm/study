#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->generatedSet->setReadOnly(true);
    ui->searchKey->setValidator(new QIntValidator(INT_MIN, INT_MAX, this));
    ui->searchResult->setReadOnly(true);
    ui->minVal->setMinimum(INT_MIN);
    ui->minVal->setMaximum(INT_MAX);
    ui->maxVal->setMinimum(INT_MIN);
    ui->maxVal->setMaximum(INT_MAX);
    ui->searchTime->setDecMode();
    setWindowTitle(tr("Lab 2"));
    newSearch = new BinarySearch();
}

MainWindow::~MainWindow()
{
    delete newSearch;
    delete ui;
}


void MainWindow::on_generateSet_button_clicked()
{
    QMessageBox allert;
    int set_size, min ,max;
    allert.setIcon(QMessageBox::Warning);
    if (ui->radioButton->isChecked())
        set_size = 1000;
    else if (ui->radioButton_2->isChecked())
        set_size = 4000;
    else if (ui->radioButton_3->isChecked())
        set_size = 6000;
    else
    {
        allert.setText("Size of the set must be chosen!");
        allert.exec();
        return;
    }
    min = ui->minVal->value();
    max = ui->maxVal->value();
    if (min > max)
    {
        allert.setText("Minimum value can't be greater than maximum!");
        allert.exec();
        return;
    }
    newSearch->generate_set(set_size, min, max);
    ui->generatedSet->clear();
    for (int i = 0; i < set_size; i++)
        ui->generatedSet->append(QString::number(newSearch->data[i]));
}

void MainWindow::on_searchButton_clicked()
{
    int key, result;
    QMessageBox allert;
    allert.setIcon(QMessageBox::Warning);
    if (!newSearch->data)
    {
        allert.setText("You must generate set before searching!");
        allert.exec();
        return;
    }
    if (ui->searchKey->text() == "")
    {
        allert.setText("You must enter the key before searching!");
        allert.exec();
        return;
    }
    key = ui->searchKey->text().toInt();
    result = newSearch->find(key);
    if (result != -1)
        ui->searchResult->setText(QString::number(result));
    else
        ui->searchResult->setText("Not found");
    ui->searchTime->display(newSearch->get_search_time());
}


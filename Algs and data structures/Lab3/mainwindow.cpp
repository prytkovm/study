#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->generatedTree->setReadOnly(true);
    ui->treeSize->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->minValue->setMinimum(INT_MIN);
    ui->minValue->setMaximum(INT_MAX);
    ui->maxValue->setMinimum(INT_MIN);
    ui->maxValue->setMaximum(INT_MAX);
    setWindowTitle(tr("Trees"));
    newTree = new Tree;
    newAVL = new AVL_tree;
}

MainWindow::~MainWindow()
{
    delete newTree;
    delete newAVL;
    delete ui->graphicsView;
    delete ui;
}

void MainWindow::on_genButton_clicked()
{
    QMessageBox allert;
    int tree_size;
    int min_val = ui->minValue->value();
    int max_val = ui->maxValue->value();
    allert.setIcon(QMessageBox::Warning);
    if (min_val > max_val)
    {
        allert.setText("Min value can't be greater than max value!");
        allert.exec();
        return;
    }
    if (ui->treeSize->text() == "")
    {
        allert.setText("You must enter tree size first!");
        allert.exec();
        return;
    }
    tree_size = ui->treeSize->text().toInt();
    if (ui->genBinary->isChecked())
    {
        newTree->generate_tree(min_val, max_val, tree_size);
        ui->graphicsView->setScene(newTree->draw_tree());
        ui->graphicsView->setAlignment(Qt::AlignTop);
    }
    else if (ui->genAVL->isChecked())
    {
        newAVL->generate_tree(min_val, max_val, tree_size);
        ui->graphicsView->setScene(newAVL->draw_tree());
        ui->graphicsView->setAlignment(Qt::AlignTop);
    }
    else
    {
        allert.setText("You must choose tree type!");
        allert.exec();
        return;
    }
}


void MainWindow::on_outButton_clicked()
{
    QMessageBox allert;
    allert.setIcon(QMessageBox::Warning);
    ui->generatedTree->clear();
    if (newTree->root || newAVL->root)
    {
        if (newTree->root)
        {
            if (ui->preorderWalk->isChecked())
                ui->generatedTree->append(QString::fromStdString(newTree->out_tree("preorder")));
            else if (ui->inorderWalk->isChecked())
                ui->generatedTree->append(QString::fromStdString(newTree->out_tree("inorder")));
            else if (ui->postorderWalk->isChecked())
                ui->generatedTree->append(QString::fromStdString(newTree->out_tree("postorder")));
        }
        else if (newAVL->root)
        {
            if (ui->preorderWalk->isChecked())
                ui->generatedTree->append(QString::fromStdString(newAVL->out_tree("preorder")));
            else if (ui->inorderWalk->isChecked())
                ui->generatedTree->append(QString::fromStdString(newAVL->out_tree("inorder")));
            else if (ui->postorderWalk->isChecked())
                ui->generatedTree->append(QString::fromStdString(newAVL->out_tree("postorder")));
        }
        else
        {
            allert.setText("You must choose tree walk algorithm!");
            allert.exec();
            return;
        }
    }
    else
    {
        allert.setText("You must generate tree first!");
        allert.exec();
        return;
    }
}


void MainWindow::on_saveButton_clicked()
{
    QImage image(ui->graphicsView->scene()->sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    ui->graphicsView->scene()->render(&painter);
    image.save("tree_graph.png");
}

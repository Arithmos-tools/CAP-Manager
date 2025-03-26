#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->process_list, &QListWidget::itemClicked, ui->capTree, &capabilitiesTree::updateTree);
    connect(ui->capTree, &QTreeWidget::itemDoubleClicked, ui->capTree, &capabilitiesTree::openInfo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_refreshButton_clicked()
{
    (ui->process_list)->updateProcess();
}


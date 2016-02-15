#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    state=Ui::DEFAULT;
    currentFile="";
    core = RRICore();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    currentFile = QFileDialog::getOpenFileName(this,
        tr("Open File"), QDir::currentPath(), tr("RRI file (*.rri);; All files (*.*)"));
    state=Ui::NEWFILE;
}

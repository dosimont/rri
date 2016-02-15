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

void MainWindow::on_timeSliceNumberSpinBox_editingFinished()
{
    state=Ui::TIMESLICE;
}

void MainWindow::on_runButton_clicked()
{

}

void MainWindow::on_homeButton_clicked()
{
    core.getParameters()->setParameter(1.0);
    ui->pEdit->setText(core.getParameters()->getParameter());
    state=Ui::PARAMETER;
}

void MainWindow::on_previousButton_clicked()
{

}

void MainWindow::on_nextButton_clicked()
{

}

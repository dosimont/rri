#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    state=Ui::STATE_DEFAULT;
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
    state=Ui::STATE_NEWFILE;
}

void MainWindow::on_timeSliceNumberSpinBox_editingFinished()
{
    if (state!=Ui::STATE_NEWFILE){
        state=Ui::STATE_TIMESLICE;
    }

}

void MainWindow::on_runButton_clicked()
{
    switch (state) {
    case Ui::STATE_NEWFILE:
        setParametersNEWFILE();
    case Ui::STATE_TIMESLICE:
        setParametersTIMESLICE();
        core.buildMicroscopicModel();
        core.initMacroscopicModels();
        core.buildMacroscopicModels();
        on_homeButton_clicked();
    case Ui::STATE_PARAMETER:
        core.selectMacroscopicModel();
    default:
        state=Ui::STATE_NOCHANGE;
        break;
    }
}

void MainWindow::on_homeButton_clicked()
{
    core.setP(rri::MAX);
    ui->pEdit->setText(core.getCurrentP());
    if (state==Ui::STATE_NOCHANGE){
        state=Ui::STATE_PARAMETER;
    }
}

void MainWindow::on_previousButton_clicked()
{
    ui->pEdit->setText(core.previousP());
    if (state==Ui::STATE_NOCHANGE){
        state=Ui::STATE_PARAMETER;
    }
}

void MainWindow::on_nextButton_clicked()
{
    ui->pEdit->setText(core.nextP());
    if (state==Ui::STATE_NOCHANGE){
        state=Ui::STATE_PARAMETER;
    }
}

void MainWindow::setParametersNEWFILE()
{
    core.getParameters()->setCurrentFileName(currentFile);
}

void MainWindow::setParametersTIMESLICE()
{
    core.getParameters()->setTimesliceNumber(ui->timeSliceNumberSpinBox->text().toInt());
}

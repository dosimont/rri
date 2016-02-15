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
    switch (state) {
    case Ui::NEWFILE:
        setParametersNEWFILE();
    case Ui::TIMESLICE:
        setParametersTIMESLICE();
        core.buildMicroscopicModel();
        core.initMacroscopicModels();
        core.buildMacroscopicModels();
        on_homeButton_clicked();
    case Ui::PARAMETER:
        core.selectMacroscopicModel();
    default:
        break;
    }
}

void MainWindow::on_homeButton_clicked()
{
    core.setP(rri::MAX);
    ui->pEdit->setText(core.getCurrentP());
    state=Ui::PARAMETER;
}

void MainWindow::on_previousButton_clicked()
{
    ui->pEdit->setText(core.previousP());
    state=Ui::PARAMETER;
}

void MainWindow::on_nextButton_clicked()
{
    ui->pEdit->setText(core.nextP());
    state=Ui::PARAMETER;
}

void MainWindow::setParametersNEWFILE()
{
    core.getParameters()->setCurrentFileName(currentFile);
}

void MainWindow::setParametersTIMESLICE()
{
    core.getParameters()->setTimesliceNumber(ui->timeSliceNumberSpinBox->text().toInt());
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <rricore.h>

namespace Ui {
class MainWindow;
enum State { DEFAULT, NEWFILE, TIMESLICE, PARAMETER, NOCHANGE };
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    Ui::State state;
    QString currentFile;

};

#endif // MAINWINDOW_H

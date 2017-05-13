#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qwtplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void DeBugInterfaceSlot();
    void PortConfigSlot();
    void OpenPortSlot();

private:
    Ui::MainWindow *ui;
    MyQwtPlot *Plot=new MyQwtPlot;
};

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#endif // MAINWINDOW_H

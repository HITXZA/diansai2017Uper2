#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qwtplot.h"
#include <QTimer>

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
    void AngleSlot();
    void AngleBoxSlot();
    void distanceAddSlot();
    void distanceSlot();
    void StopSlot();

private:
    Ui::MainWindow *ui;
    MyQwtPlot *Plot=new MyQwtPlot;
    void SendData();
    QTimer *Reflash=new QTimer;
};

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#endif // MAINWINDOW_H

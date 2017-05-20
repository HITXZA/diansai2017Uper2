#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QDialog>
#include "qwtplot.h"

namespace Ui {
class debugwindow;
}

class debugwindow : public QDialog
{
    Q_OBJECT

public:
    explicit debugwindow(QWidget *parent = 0);
    ~debugwindow();
public slots:
    void PortConfigSlot();
    void OpenPortSlot();
    void PSlot();
    void ISlot();
    void DSlot();
    void PBoxSlot();
    void IBoxSlot();
    void DBoxSlot();
    void AngleSlot();
    void AngleBoxSlot();
    void DistanceaddSlot();
    void DistanceSlot();
    void StopSlot();


private:
    Ui::debugwindow *ui;
    MyQwtPlot *Plot=new MyQwtPlot;
     void SendData();
};


#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#endif // DEBUGWINDOW_H

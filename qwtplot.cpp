#include "qwtplot.h"
#include "port.h"
#include <QTimer>
MyQwtPlot::MyQwtPlot()
{
    this->Timei=0;
}

void MyQwtPlot::QwtInit(QwtPlot *Plot)
{
    this->MyPlot=Plot;
    Plot->enableAxis(QwtPlot::xTop,false);
    Plot->enableAxis(QwtPlot::xBottom,true);
    Plot->enableAxis(QwtPlot::yLeft,false);
    Plot->enableAxis(QwtPlot::yRight,true);
    Plot->setAxisAutoScale(QwtPlot::yLeft,true);
    Plot->setAxisAutoScale(QwtPlot::xBottom,true);

    QwtPlotMagnifier *Magnifer=new QwtPlotMagnifier(Plot->canvas());//设置鼠标滚动
    QwtPlotPanner *Panner=new QwtPlotPanner(Plot->canvas());

    this->Curve->attach(Plot);
    this->Curve->setStyle(QwtPlotCurve::Lines);
    this->Curve->setCurveAttribute(QwtPlotCurve::Fitted,true);//是曲线更光滑
    this->Curve->setPen(Qt::blue);

    this->Grid->setMajorPen(Qt::gray,0,Qt::DotLine);
    this->Grid->setMinorPen(Qt::gray,0,Qt::DotLine);
    this->Grid->enableX(true);
    this->Grid->enableY(true);
    this->Grid->enableYMin(true);
    this->Grid->enableXMin(false);
    this->Grid->attach(Plot);

    Plot->setAxisScale(QwtPlot::yRight,0,90);
    Plot->setAxisScale(QwtPlot::xBottom,0,500);

}

void MyQwtPlot::QwtReceiveSlot()
{

    if(Port.bytesAvailable()>=50)
    {
       QByteArray buf;
       buf.clear();
       buf =Port.read(1);
       this->yData.append(10.0);
       this->xData.append(Timei);
       this->Curve->setSamples(this->xData,this->yData);
       qDebug()<<buf;
       MyPlot->replot();
       Timei++;
       if(Timei>500)
       {
            MyPlot->setAxisScale(QwtPlot::xBottom,Timei-500,Timei);
       }
     }




}

void MyQwtPlot::CleanSlot()
{
    this->xData.clear();
    this->yData.clear();
    this->Timei=0;
    this->Curve->setSamples(this->xData,this->yData);

    MyPlot->setAxisScale(QwtPlot::yLeft,0,90);
    MyPlot->setAxisScale(QwtPlot::xBottom,0,50);

    MyPlot->replot();
}

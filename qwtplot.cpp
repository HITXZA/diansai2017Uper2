#include "qwtplot.h"
#include "port.h"

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
    Plot->setAxisScale(QwtPlot::xBottom,0,50);

}

void MyQwtPlot::QwtReceiveSlot()
{
    int data[8*2+8+100];
#define number 1
    if(Port.bytesAvailable()>=number*2+8)
    {
        QByteArray buf;
        QString temp;
        for(int k=0;k<number*2+8;k++)
        {
            buf =Port.read(1);
            bool ok=true;
            temp=buf.toHex();
            data[k]=temp.toInt(&ok,16);
            buf.clear();
            temp.clear();
        }

       for(int i=0;i<number+4;i++)
       {
           if(data[i]==3&&data[i+1]==252&&data[i+2+number]==0xfc&&data[i+3+number]==0x03)
           {
               for(int j=0;j<number;j++)
               {
                   this->yData.append(data[i+2+j]);
               }
               this->xData.append(Timei);
               this->Curve->setSamples(this->xData,this->yData);
               MyPlot->replot();
               qDebug()<<yData;//画图数据有bug
               Timei++;
               if(Timei>50)
               {
                    MyPlot->setAxisScale(QwtPlot::xBottom,Timei-50,Timei);
               }
               break;
           }
       }   
    }
}

void MyQwtPlot::CleanSlot()
{
    this->xData.clear();
    this->yData.clear();
    this->Curve->setSamples(this->xData,this->yData);

    MyPlot->setAxisScale(QwtPlot::yLeft,0,90);
    MyPlot->setAxisScale(QwtPlot::xBottom,0,50);

    MyPlot->replot();
}

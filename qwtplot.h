#ifndef QWTPLOT_H
#define QWTPLOT_H

#include <QObject>
#include <QWidget>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_directpainter.h>
#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_item.h>
#include <QVector>
#include <qwt_legend.h>
#include <qmath.h>
#include <QPointF>
#include <QWidget>

class MyQwtPlot : public QwtPlotGrid , QwtPlotCurve,QObject,QMetaObject,QWidget
{

    Q_OBJECT
public:
    MyQwtPlot();
    void QwtInit(QwtPlot *Plot);
    QwtPlotGrid *Grid=new QwtPlotGrid;              //网格图
    QwtPlotCurve *Curve=new QwtPlotCurve;           //笔刷

public slots:
    void CleanSlot();
    void QwtReceiveSlot();
private:
    QVector<double> yData;
    QVector<double> xData;
    int Timei;
    QwtPlot *MyPlot;

    /*
    QTimer *QwtTimer=new QTimer(this);              //设置定时器*/


};

#endif // QWTPLOT_H

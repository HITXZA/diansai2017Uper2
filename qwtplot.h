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

class QwtPlot : public QwtPlotGrid , QwtPlotCurve
{
public:
    QwtPlot();
};

#endif // QWTPLOT_H

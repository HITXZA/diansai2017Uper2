#ifndef CONFIO_H
#define CONFIO_H

#include <QObject>
#include <QWidget>
#include <QSettings>

class confio:public QSettings
{
public:
    confio();
};

#endif // CONFIO_H

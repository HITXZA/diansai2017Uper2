#include "debugwindow.h"
#include "ui_debugwindow.h"

debugwindow::debugwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::debugwindow)
{
    ui->setupUi(this);
}

debugwindow::~debugwindow()
{
    delete ui;
}

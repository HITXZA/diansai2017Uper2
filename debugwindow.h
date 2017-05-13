#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QDialog>

namespace Ui {
class debugwindow;
}

class debugwindow : public QDialog
{
    Q_OBJECT

public:
    explicit debugwindow(QWidget *parent = 0);
    ~debugwindow();

private:
    Ui::debugwindow *ui;
};


#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#endif // DEBUGWINDOW_H

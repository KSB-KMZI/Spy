#ifndef GRABBER_H
#define GRABBER_H

#include <QDialog>
#include <fstream>
using namespace std;

namespace Ui {
class Grabber;
}

class Grabber : public QDialog
{
    Q_OBJECT

public:
    explicit Grabber(QWidget *parent = 0);
    ~Grabber();

private slots:
    void on_GC_clicked();

private:
    Ui::Grabber *ui;
};

#endif // GRABBER_H

#ifndef SCREENSHOOTER_H
#define SCREENSHOOTER_H

#include <QDialog>
#include <fstream>
using namespace std;

namespace Ui {
class screenshooter;
}

class screenshooter : public QDialog
{
    Q_OBJECT

public:
    explicit screenshooter(QWidget *parent = 0);
    ~screenshooter();

private slots:
    void on_GC_clicked();

private:
    Ui::screenshooter *ui;
};

#endif // SCREENSHOOTER_H

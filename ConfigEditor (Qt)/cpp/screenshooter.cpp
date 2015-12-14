#include "screenshooter.h"
#include "ui_screenshooter.h"

screenshooter::screenshooter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::screenshooter)
{
    ui->setupUi(this);
}

screenshooter::~screenshooter()
{
    delete ui;
}

void screenshooter::on_GC_clicked()
{
    ofstream ofst, oofst;
    ofst.open("Sconfig.txt", ios::out);
    oofst.open("Sconfig.ksb", ios::out);

    ofst << !(ui->RSC->isChecked()) << endl;
    ofst << ui->SSC->value();

    oofst << !(ui->RSC->isChecked()) << endl;
    oofst << ui->SSC->value();

    ofst.close();
    oofst.close();

    close();
}

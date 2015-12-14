#include "keylogger.h"
#include "ui_keylogger.h"

Keylogger::Keylogger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Keylogger)
{
    ui->setupUi(this);
}

Keylogger::~Keylogger()
{
    delete ui;
}

void Keylogger::on_GC_clicked()
{
    ofstream ofst, oofst;
    ofst.open("Kconfig.txt", ios::out);
    oofst.open("Kconfig.ksb",ios::out);

    ofst << !(ui->RKL->isChecked());
    oofst << !(ui->RKL->isChecked());

    ofst.close();
    oofst.close();

    close();
}

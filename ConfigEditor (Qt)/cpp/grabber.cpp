#include "grabber.h"
#include "ui_grabber.h"

Grabber::Grabber(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Grabber)
{
    ui->setupUi(this);
}

Grabber::~Grabber()
{
    delete ui;
}

void Grabber::on_GC_clicked()
{
    ofstream ofst, oofst;
    ofst.open("Gconfig.txt", ios::out);
    oofst.open("Gconfig.ksb", ios::out);

    ofst << !(ui->CRun->isChecked()) << endl;
    ofst << ui->SHI->value() << endl;
    ofst << ui->SSC->value() << endl;
    ofst << ui->SSI->value() << endl;
    ofst << ui->SNI->value() << endl;
    ofst << ui->SES->value() << endl;
    ofst << ui->SSP->value() << endl;
    ofst << ui->WHW->isChecked() << endl;
    ofst << ui->WSC->isChecked() << endl;
    ofst << ui->WSI->isChecked() << endl;
    ofst << ui->WNI->isChecked() << endl;
    ofst << ui->WES->isChecked() << endl;
    ofst << ui->WSP->isChecked();

    oofst << !(ui->CRun->isChecked()) << endl;
    oofst << ui->SHI->value() << endl;
    oofst << ui->SSC->value() << endl;
    oofst << ui->SSI->value() << endl;
    oofst << ui->SNI->value() << endl;
    oofst << ui->SES->value() << endl;
    oofst << ui->SSP->value() << endl;
    oofst << ui->WHW->isChecked() << endl;
    oofst << ui->WSC->isChecked() << endl;
    oofst << ui->WSI->isChecked() << endl;
    oofst << ui->WNI->isChecked() << endl;
    oofst << ui->WES->isChecked() << endl;
    oofst << ui->WSP->isChecked();

    ofst.close();
    oofst.close();

    close();

}

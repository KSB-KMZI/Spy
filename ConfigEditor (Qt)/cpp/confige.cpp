#include "confige.h"
#include "ui_confige.h"

ConfigE::ConfigE(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigE)
{
    ui->setupUi(this);
}

ConfigE::~ConfigE()
{
    delete ui;
}

void ConfigE::on_CallGrabber_clicked()
{
    G.setModal(true);
    G.exec();
}

void ConfigE::on_CallKeylogger_clicked()
{
    K.setModal(true);
    K.exec();
}

void ConfigE::on_CallScreenshooter_clicked()
{
    S.setModal(true);
    S.exec();
}

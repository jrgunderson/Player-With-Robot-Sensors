#include "opnpartic.h"
#include "ui_opnpartic.h"

OPNPartic::OPNPartic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OPNPartic)
{
    ui->setupUi(this);
}

OPNPartic::~OPNPartic()
{
    delete ui;
}

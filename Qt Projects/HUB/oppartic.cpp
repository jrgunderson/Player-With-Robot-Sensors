#include "oppartic.h"
#include "ui_oppartic.h"

OpPartic::OpPartic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpPartic)
{
    ui->setupUi(this);
}

OpPartic::~OpPartic()
{
    delete ui;
}

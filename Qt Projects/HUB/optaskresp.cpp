#include "optaskresp.h"
#include "ui_optaskresp.h"



OpTaskResp::OpTaskResp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpTaskResp)
{
    ui->setupUi(this);
}
void OpTaskResp::init(TaskAllocator *ta){
    connect(this,SIGNAL(opResponse(bool,double,double,int)),
            ta, SLOT(receiveOpResponse(bool, double, double, int)));
}

OpTaskResp::~OpTaskResp()
{
    delete ui;
}

void OpTaskResp::on_submitButton_clicked()
{
    qDebug() << "About to send OP Response message";
    bool checked = ui->yesButton->isChecked();
    int x;

    //Default Position is (0,0)
    if(ui->xText->text().size() == 0){
        x = 0;
    }
    else{
        x = ui->xText->text().toDouble();
    }

    int y;
    if(ui->yText->text().size() == 0){
        y = 0;
    }
    else{
        y = ui->yText->text().toDouble();
    }
    int slider = ui->busySlider->value();
    emit opResponse(checked,x,y,slider);
    qDebug() << "Message sent";
    QString s = "Operator Responded";
    emit logIt(s);
    ui->xText->clear();
    ui->yText->clear();
    ui->busySlider->setValue(0);
    this->close();
}

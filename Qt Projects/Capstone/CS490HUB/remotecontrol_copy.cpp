#include "remotecontrol.h"
#include "ui_remotecontrol.h"

RemoteControl::RemoteControl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoteControl)
{
    ui->setupUi(this);
}

RemoteControl::~RemoteControl()
{
    delete ui;
}

void RemoteControl::init(TaskAllocator *ta){
    //connect(this,SIGNAL(opResponse(bool,double,double,int)),
    //        ta, SLOT(receiveOpResponse(bool, double, double, int)));
}

void RemoteControl::on_emStop_clicked()
{
    //Send message to robot to stop
}

void RemoteControl::on_contRobot_clicked()
{
    //take over robot and use buttons below to move root
}

void RemoteControl::on_joinTeam_clicked()
{
    //Add operator to team
}

void RemoteControl::on_returnAut_clicked()
{
    //Remove operator from team?
    //If operator is controlling robot, put them back to autonomous
}

void RemoteControl::on_moveForward_clicked()
{
    //Send message to robot to move forward
}

void RemoteControl::on_moveRight_clicked()
{
    //Send message to robot to move right
}

void RemoteControl::on_moveLeft_clicked()
{
    //Send message to robot to move left
}

void RemoteControl::on_moveBack_clicked()
{
    //Send message to robot to move back
}

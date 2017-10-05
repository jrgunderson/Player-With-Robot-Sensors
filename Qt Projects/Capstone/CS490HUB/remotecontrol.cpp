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

void RemoteControl::init(TaskAllocator *ta, CommunicatorWrapper *com){
    connect(this,SIGNAL(moveCommand(int, int)),
            com, SLOT(sendMove(int,int)));
    ui->roboSelect->setMaximum(2);
}

void RemoteControl::on_emStop_clicked()
{
    //Send message to robot to stop
    int i = ui->roboSelect->value();
    int m = 4;
    emit(moveCommand(i, m));
}

void RemoteControl::on_contRobot_clicked()
{
    //take over robot and use buttons below to move root
}

void RemoteControl::on_joinTeam_clicked()
{
    //Add operator to team (P2P)
}

void RemoteControl::on_returnAut_clicked()
{
    //Remove operator from team?
    //If operator is controlling robot, put them back to autonomous
    this->hide();
    emit(closed());
}

void RemoteControl::on_moveForward_clicked()
{
    //Send message to robot to move forward
    int i = ui->roboSelect->value();
    int m = 0;
    emit(moveCommand(i, m));
}

void RemoteControl::on_moveRight_clicked()
{
    //Send message to robot to move right
    int i = ui->roboSelect->value();
    int m = 3;
    emit(moveCommand(i, m));
}

void RemoteControl::on_moveLeft_clicked()
{
    //Send message to robot to move left
    int i = ui->roboSelect->value();
    int m = 2;
    emit(moveCommand(i, m));
}

void RemoteControl::on_moveBack_clicked()
{
    //Send message to robot to move back
    int i = ui->roboSelect->value();
    int m = 1;
    emit(moveCommand(i, m));
}

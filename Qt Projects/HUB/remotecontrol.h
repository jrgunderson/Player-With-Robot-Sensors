#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include <QDialog>
#include "taskallocator.h"
#include "communicatorwrapper.h"

namespace Ui {
class RemoteControl;
}

class RemoteControl : public QDialog
{
    Q_OBJECT

public:
    explicit RemoteControl(QWidget *parent = 0);
    void init(TaskAllocator* ta, CommunicatorWrapper *com);
    ~RemoteControl();

private slots:
    void on_emStop_clicked();

    void on_contRobot_clicked();

    void on_joinTeam_clicked();

    void on_returnAut_clicked();

    void on_moveForward_clicked();

    void on_moveRight_clicked();

    void on_moveLeft_clicked();

    void on_moveBack_clicked();

private:
    Ui::RemoteControl *ui;

signals:
    void closed();
    void moveCommand(int,int);
};

#endif // REMOTECONTROL_H

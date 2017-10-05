#include "taskalowindow.h"
#include "ui_taskalowindow.h"

QStandardItemModel *model3;
QStandardItem *teamText;
QList<QString> teams;

TaskAloWindow::TaskAloWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskAloWindow)
{
    ui->setupUi(this);
}
void TaskAloWindow::init(){
    QStringList hHeader;
    hHeader.append("Team Members");
    model3 = new QStandardItemModel(0,1,this);
    model3->setHorizontalHeaderLabels(hHeader);
    ui->teamTable->setModel(model3);
}

TaskAloWindow::~TaskAloWindow()
{
    delete ui;
}
void TaskAloWindow::add(int i, QString s, QString x){
    teams.append(x);
    teamText = new QStandardItem(s);
    model3->setItem(i,teamText);
    ui->teamAssign->setMaximum(teams.size());
}

void TaskAloWindow::on_startButton_clicked()
{
    this->hide();
    int x = ui->teamAssign->value()-1;
    QString z = "Team assigned: ";
    QString s = z + teams.at(x);
    teams.clear();
    emit logIt(s);
}
void TaskAloWindow::closeIt(){
    if(this->isVisible()){
        this->hide();
        QString z = "Team assigned: ";
        QString s = z + teams.first();
        emit logIt(s);
    }
}

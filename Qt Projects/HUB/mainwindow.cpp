#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <QThread>

char *ip_ad1 = "192.168.0.15";
char *ip_ad2 = "192.168.0.15";
char *ip_ad3 = "192.168.0.15";

char*temp = "-Xmx256m";

int port = 6665;

TaskAllocator* ta;
CommunicatorWrapper* com;

int teamNum = 0;
int taskNum = 0;

QStandardItemModel *model;
QStandardItemModel *model2;
QStandardItem *t1W;
QStandardItem *t1X;
QStandardItem *t1Y;
QStandardItem *t2W;
QStandardItem *t2X;
QStandardItem *t2Y;
QStandardItem *t3W;
QStandardItem *t3X;
QStandardItem *t3Y;
QStandardItem *t4W;
QStandardItem *t4X;
QStandardItem *t4Y;
QStandardItem *text;

OpTaskResp *opWindow;
TaskAloWindow *taskWindow;
RemoteControl *teleopWindow;
ErrorWindow *errWindow;

QTimer* mTimer;

int logSize = 0;
QString taskFile = "tasks.txt";

QThread receiveThread;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    ta = new TaskAllocator();
    opWindow = new OpTaskResp(this);
    taskWindow = new TaskAloWindow();
    errWindow = new ErrorWindow();
    com = new CommunicatorWrapper(ip_ad1, ip_ad2, ip_ad3, port);

    connect(ta,SIGNAL(winnerFound(QList<Team>)),
            this, SLOT(onWinnerFound(QList<Team>)));
    connect(opWindow,SIGNAL(logIt(QString)),
            this, SLOT(addToLog(QString)));
    connect(taskWindow,SIGNAL(logIt(QString)),
            this, SLOT(addToLog(QString)));
    connect(teleopWindow,SIGNAL(logIt(QString)),
            this, SLOT(addToLog(QString)));
    connect(teleopWindow,SIGNAL(closed()),
            this, SLOT(changeSlider()));



    QStringList hHeader;
    hHeader.append("Weight");
    hHeader.append("X");
    hHeader.append("Y");
    model = new QStandardItemModel(0,3,this);
    model->setHorizontalHeaderLabels(hHeader);
    ui->taskTable->setModel(model);
    ui->taskTable->horizontalHeader()->setStretchLastSection(true);


    QStringList hHeader2;
    hHeader2.append("Log");
    model2 = new QStandardItemModel(0,1,this);
    model2->setHorizontalHeaderLabels(hHeader2);
    ui->logTable->setModel(model2);
    ui->logTable->horizontalHeader()->setStretchLastSection(true);

    ui->slidAutSlider->setTickInterval(33);
    ui->slidAutSlider->setSingleStep(33);
    ui->slidAutSlider->setTickPosition(QSlider::TicksBothSides);

    ui->taskAssign->setMaximum(0);

    QString fileName = "C:/Users/icsax/Desktop/Original/Sliding_Autonomy_SW/CS490HUB/" + taskFile;
    QFile file(fileName);
    QString s = file.symLinkTarget();
    qDebug() << s;
    QFileInfo fileInfo(file);
    qDebug() << fileInfo.absoluteFilePath();

    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        while(!in.atEnd()){
            QString line = in.readLine();
            QStringList task = line.split(",");
            int w = task[0].toInt();
            double x = task[1].toDouble();
            double y = task[2].toDouble();

            Task newTask(w,x,y);
            ta->addTask(newTask);
            QString s = "New Task Added";
            addToLog(s);
            taskNum++;
            ui->taskAssign->setMinimum(1);
            ui->taskAssign->setMaximum(taskNum);
            t1W = new QStandardItem(QString::number(w));
            model->setItem(taskNum-1, 0, t1W);
            t1X = new QStandardItem(QString::number(x));
            model->setItem(taskNum-1, 1, t1X);
            t1Y = new QStandardItem(QString::number(y));
            model->setItem(taskNum-1, 2, t1Y);
        }
        file.close();
    }else{
        qDebug() << file.errorString();
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_submitTaskButton_clicked()
{
    ui->taskAssign->setMaximum(taskNum);
    double w = ui->WoBText->text().toDouble();
    double x = ui->xText->text().toDouble();
    double y = ui->yText->text().toDouble();
    Task newTask(w,x,y);
    ta->addTask(newTask);
    //QList<Task> t = ta->getTasks();
    QString s = "New Task Added";
    addToLog(s);


    taskNum++;
    ui->taskAssign->setMaximum(taskNum);
    t1W = new QStandardItem(QString::number(w));
    model->setItem(taskNum-1, 0, t1W);
    t1X = new QStandardItem(QString::number(x));
    model->setItem(taskNum-1, 1, t1X);
    t1Y = new QStandardItem(QString::number(y));
    model->setItem(taskNum-1, 2, t1Y);
    /*switch(taskNum){ //Max 4 Tasks for now
    case 1:
        t1W = new QStandardItem(QString::number(w));
        model->setItem(taskNum-1, 0, t1W);
        t1X = new QStandardItem(QString::number(x));
        model->setItem(taskNum-1, 1, t1X);
        t1Y = new QStandardItem(QString::number(y));
        model->setItem(taskNum-1, 2, t1Y);
        break;
   case 2:
        t2W = new QStandardItem(QString::number(w));
        model->setItem(taskNum-1, 0, t2W);
        t2X = new QStandardItem(QString::number(x));
        model->setItem(taskNum-1, 1, t2X);
        t2Y = new QStandardItem(QString::number(y));
        model->setItem(taskNum-1, 2, t2Y);
        break;
    case 3:
        t3W = new QStandardItem(QString::number(w));
        model->setItem(taskNum-1, 0, t3W);
        t3X = new QStandardItem(QString::number(x));
        model->setItem(taskNum-1, 1, t3X);
        t3Y = new QStandardItem(QString::number(y));
        model->setItem(taskNum-1, 2, t3Y);
        break;
    case 4:
        t4W = new QStandardItem(QString::number(w));
        model->setItem(taskNum-1, 0, t4W);
        t4X = new QStandardItem(QString::number(x));
        model->setItem(taskNum-1, 1, t4X);
        t4Y = new QStandardItem(QString::number(y));
        model->setItem(taskNum-1, 2, t4Y);
        break;
    }*/
    ui->WoBText->clear();
    ui->xText->clear();
    ui->yText->clear();
}
void MainWindow::on_taskAloButton_clicked()
{
    QString s = "Assigning Task";
    addToLog(s);
    //Send signal to robots asking for bid
    com->sendTask();
    //Collect Bids
    mTimer = new QTimer(this);
    mTimer->setSingleShot(true);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(continueTaskAlo()));
    mTimer->start(5000);
}
void MainWindow::continueTaskAlo(){
    //Open New Window
    int i = ui->taskAssign->value();
    Task t = ta->getTask(i-1);

    //Print out Task to console to check if correct task is being chosen


    //Data to test Task Allocation


    //ta->addBid(Bid(1,5,10));
    //ta->addBid(Bid(2,8,10));
    //ta->addBid(Bid(3,3,8));
    //ta->addBid(Bid(4,6,9));

    ta->setCurrent(i-1);

    //Open Window for Operator

    opWindow->init(ta);
    opWindow->show();
}

void MainWindow::on_slidAutSlider_valueChanged(int value)
{

    if(value == 66) {
        teleopWindow = new RemoteControl();
        teleopWindow->init(ta,com);
        teleopWindow->show();
    }
}
void MainWindow::onWinnerFound(QList<Team> teams)
{
    QString s = "Team Found";
    addToLog(s);
    taskWindow->init();
    for(int i = 0; i < teams.size(); i++) {
        if(teams[i].size() != 0){
            QString s = "RN: ";


            for(int j = 0; j < teams[i].size(); j++) {
                int temp = teams[i].getBid(j).getID();
                if(temp == -1){
                    s.append("H");
                }
                else{
                    s.append(QString::number(temp));
                }
                if(j != teams[i].size()-1){
                    s.append(", ");
                }
            }
            QString x = s;
            s = s + " Str: " + QString::number(teams[i].getTeamStrength());

            taskWindow->add(i,s,x);
        }
    }

    taskWindow->show();
    mTimer = new QTimer(this);
    mTimer->setSingleShot(true);
    connect(mTimer, SIGNAL(timeout()), taskWindow, SLOT(closeIt()));
    mTimer->start(5000);
}


//Camera stream
void MainWindow::on_pushButton_clicked()
{

}
void MainWindow::addToLog(QString s){
    text = new QStandardItem(s);
    model2->setItem(logSize,text);
    logSize++;
}
void MainWindow::receiveBid(int rn, int s, double d){
    Bid b = Bid(rn, s, d);
    ta->addBid(b);
}
void MainWindow::receiveError(char *emsg){
    errWindow->addMessage(emsg);
    errWindow->show();
}
void MainWindow::teleopClosed(){
    ui->slidAutSlider->setValue(0);
    com->sendStart();
}

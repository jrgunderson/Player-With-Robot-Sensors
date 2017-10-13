#include "errorwindow.h"
#include "ui_errorwindow.h"

QStandardItemModel *model4;
QStandardItem *errorText;

ErrorWindow::ErrorWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ErrorWindow)
{
    ui->setupUi(this);
    QStringList hHeader;
    hHeader.append("Errors: ");
    model4 = new QStandardItemModel(0,1,this);
    model4->setHorizontalHeaderLabels(hHeader);
    ui->listView->setModel(model4);
}

void ErrorWindow::addMessage(char *msg){
    errorText = new QStandardItem(msg);
    model4->setItem(0,errorText);
}

ErrorWindow::~ErrorWindow()
{
    delete ui;
}

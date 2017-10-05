#ifndef OPTASKRESP_H
#define OPTASKRESP_H

#include <QDialog>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "taskallocator.h"

namespace Ui {
class OpTaskResp;
}

class OpTaskResp : public QDialog
{
    Q_OBJECT

public:
    explicit OpTaskResp(QWidget *parent = 0);
    void init(TaskAllocator* ta);
    ~OpTaskResp();
public slots:

private slots:
    void on_submitButton_clicked();

signals:
    void opResponse(bool available, double x, double y, int busy);
    void logIt(QString s);

private:
    Ui::OpTaskResp *ui;
    QTcpSocket *socket;
};

#endif // OPTASKRESP_H

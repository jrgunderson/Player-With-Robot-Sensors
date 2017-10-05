#ifndef TASKALOWINDOW_H
#define TASKALOWINDOW_H

#include <QWidget>
#include <QStandardItemModel>
#include <QDebug>

namespace Ui {
class TaskAloWindow;
}

class TaskAloWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TaskAloWindow(QWidget *parent = 0);
    ~TaskAloWindow();
    void init();
    void add(int i, QString s, QString x);

private slots:
    void on_startButton_clicked();

public slots:
    void closeIt();

private:
    Ui::TaskAloWindow *ui;

signals:
    void logIt(QString s);
};

#endif // TASKALOWINDOW_H

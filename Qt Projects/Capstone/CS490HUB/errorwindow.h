#ifndef ERRORWINDOW_H
#define ERRORWINDOW_H

#include <QWidget>
#include <QStandardItemModel>
#include <QDebug>

namespace Ui {
class ErrorWindow;
}

class ErrorWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ErrorWindow(QWidget *parent = 0);
    void addMessage(char *msg);
    ~ErrorWindow();

private:
    Ui::ErrorWindow *ui;
};

#endif // ERRORWINDOW_H

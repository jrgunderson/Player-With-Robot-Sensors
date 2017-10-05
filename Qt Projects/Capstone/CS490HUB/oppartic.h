#ifndef OPPARTIC_H
#define OPPARTIC_H

#include <QDialog>

namespace Ui {
class OpPartic;
}

class OpPartic : public QDialog
{
    Q_OBJECT

public:
    explicit OpPartic(QWidget *parent = 0);
    ~OpPartic();

private:
    Ui::OpPartic *ui;
};

#endif // OPPARTIC_H

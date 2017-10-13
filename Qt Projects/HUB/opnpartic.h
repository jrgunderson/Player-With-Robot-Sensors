#ifndef OPNPARTIC_H
#define OPNPARTIC_H

#include <QDialog>

namespace Ui {
class OPNPartic;
}

class OPNPartic : public QDialog
{
    Q_OBJECT

public:
    explicit OPNPartic(QWidget *parent = 0);
    ~OPNPartic();

private:
    Ui::OPNPartic *ui;
};

#endif // OPNPARTIC_H

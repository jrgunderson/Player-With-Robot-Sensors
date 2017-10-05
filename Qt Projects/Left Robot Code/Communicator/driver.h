#ifndef DRIVER_H
#define DRIVER_H

#include <QAbstractItemModel>
#include "communicator.h"

class Driver : public QObject
{
    Q_OBJECT

public:
    explicit Driver(QObject *parent = 0);

private:
};

#endif // DRIVER_H

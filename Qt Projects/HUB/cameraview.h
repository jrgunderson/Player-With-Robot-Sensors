#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include <QWidget>

//This Class will connect to the robot and access its camera, and show camera feed
namespace Ui {
class CameraView;
}

class CameraView : public QWidget
{
    Q_OBJECT

public:
    explicit CameraView(QWidget *parent = 0);
    ~CameraView();

private:
    Ui::CameraView *ui;
};

#endif // CAMERAVIEW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    float PL(float f, float d);
    float calculatePenetrationLoss(float distance);
    int countObstaclesOnRay(int x1, int y1, int x2, int y2);
    void drawObstacles(QPainter& p, int maxX, int maxY);
    void colorizePixels(QPainter& p, int maxX, int maxY, float signalPower);

private:
    // S
};

#endif // MAINWINDOW_H


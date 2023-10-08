#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool isGlassWall(int x, int y);
    bool isIrrGlassWall(int x, int y);
    bool isConcreteWall(int x, int y);
    bool isWoodOrGypsumWall(int x, int y);

private:
    void drawSignalMap(QPainter &painter);
    float calculateSignalPower(int x, int y);
    float pathLoss(float distance);

    QGraphicsScene *scene;
    int maxX;
    int maxY;
    double onePixDistance;
    int txPower;
    int antGain;
    float freq;
};

#endif // MAINWINDOW_H

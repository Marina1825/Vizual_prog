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

    bool isGlassWall(int x, int y, int (&matrixR)[4][4]);
    bool isIrrGlassWall(int x, int y, int (&matrixR)[4][4]);
    bool isConcreteWall(int x, int y, int (&matrixR)[4][4]);
    bool isWoodOrGypsumWall(int x, int y, int (&matrixR)[4][4]);
    void drawLine(int x1, int y1, int x2, int y2, int (&matrixR)[4][4]);
    int** prepztstvie(int x1, int y1, int x2, int y2, int (&matrixR)[4][4]);

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

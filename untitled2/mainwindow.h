#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>

enum class type_material : int{
    NO_MATERIAL = 0,
    GLASS,
    IRR_GLASS,
    CONCRETE,
    WOOD,
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void drawSignalStrength(QPixmap *map);
    void setupMap();
    void createColorMap();

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

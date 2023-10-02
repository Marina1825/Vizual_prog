/*#ifndef MAINWINDOW_H
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
    // Äîáàâüòå ñâîè ïðèâàòíûå ïåðåìåííûå è ìåòîäû çäåñü, åñëè íåîáõîäèìî
};

#endif // MAINWINDOW_H*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QPixmap>

//QT_BEGIN_NAMESPACE
//namespace Ui {class MainWindow;}
//QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT
    float PL(float f, float d);

    /*private slots:
    void on_stackedWidget_itemChanged();
    ~MainWindow();*/

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        void draw_gradient();
        QPixmap *map;
        QGraphicsScene* scene;
        QGraphicsView *view;

        QLabel *label_;
        QGroupBox *gradientGroupBox_;

};
#endif // MAINWINDOW_H

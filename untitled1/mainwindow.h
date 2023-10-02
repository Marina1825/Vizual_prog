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

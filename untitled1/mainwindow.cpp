/*#include "mainwindow.h"
#include <QtWidgets>
#include <QGroupBox>
#include <QWidget>
#include <cmath>
#include <cstdlib>

float MainWindow::PL(float f, float d) {
    return 28 + 22 * log10(f) + 20 * log10(d);
}

float calculatePenetrationLoss(float distance, int col_wall, float material_wall) {
    //float PL_tw = 20; //[dB]
    float PL_b = ;
    float PL_in = 0.5;
    float PL_TW = P(col_wall) * 10 * (col_wall * 10 * (material_wall / -10));
    PL= PL_b + PLtw + PL_in + N(0, q*q)

    // Здесь используется какая-то формула для расчета затухания,
    // соответствующая спецификации 3GPP TR 38.901 (7.4.3.1 O2I building penetration loss)
    // Замените этот код вашей формулой

    return 0; /* ваш расчет
}

int countObstaclesOnRay(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int error = dx - dy;
    int obstacles = 0;

    while (x1 != x2 || y1 != y2) {
        // Проверяем текущий пиксель на наличие препятствия
        // Не забудьте определить, как проверять препятствия в данном пикселе

        if (/* Ваш код проверки препятствия ) {
            obstacles++;
        }

        int error2 = 2 * error;

        if (error2 > -dy) {
            error -= dy;
            x1 += sx;
        }

        if (error2 < dx) {
            error += dx;
            y1 += sy;
        }
    }

    return obstacles;
}

void MainWindow::drawObstacles(QPainter& p, int maxX, int maxY) {
    // Количество препятствий
    int numObstacles = rand() % 50 + 10; // От 10 до 60 препятствий

    for (int i = 0; i < numObstacles; i++) {
        int type = rand() % 4; // Случайный выбор типа препятствия
        int material = rand() % 4; // Случайный выбор материала

        QColor color;

        // Выбор цвета на основе материала
        switch (material) {
        case 0: color = Qt::gray; break; // Стеклопакет 2+0.2f
        case 1: color = Qt::cyan; break; // IRR стекло 23+0.3f
        case 2: color = Qt::darkGray; break; // Бетон 5+4f
        case 3: color = Qt::green; break; // Дерево\гипсокартон 4.85+0.12f
        }

        p.setBrush(color);
        p.setPen(color);

        // Рисование препятствия на основе его типа
        switch (type) {
        case 0: {
            // Круг
            int x = rand() % maxX;
            int y = rand() % maxY;
            int r = rand() % 50 + 10;
            p.drawEllipse(x, y, r, r);
            break;
        }
        case 1: {
            // Прямоугольник
            int x = rand() % maxX;
            int y = rand() % maxY;
            int w = rand() % 100 + 20;
            int h = rand() % 100 + 20;
            p.drawRect(x, y, w, h);
            break;
        }
        case 2: {
            // Линия
            int x1 = rand() % maxX;
            int y1 = rand() % maxY;
            int x2 = rand() % maxX;
            int y2 = rand() % maxY;
            p.drawLine(x1, y1, x2, y2);

            // Вызываем функцию для подсчета препятствий на луче
            int obstacles = countObstaclesOnRay(cellPosX, cellPosY, x2, y2);

            // Используйте значение obstacles по своему усмотрению

            break;
        }
        case 3: {
            // Эллипс
            int x = rand() % maxX;
            int y = rand() % maxY;
            int w = rand() % 100 + 20;
            int h = rand() % 50 + 10;
            p.drawEllipse(x, y, w, h);
            break;
        }
        }
    }
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    QGraphicsScene* scene = new QGraphicsScene();
    int maxX = 1000;
    int maxY = 1000;
    int col_wall = 0;
    float material_wall = 0;
    double onePixDistance = 10; //[m]
    int TxPower = 10;           // [dBm]
    int antGain = 6;            // [dBi]
    float freq = 6;//не смей меня менять, о смертный человек, иначе ты познаешь боль, мучения, ведь чтоб сменить меня на 5 тебе придется цыкл написать // [GHz]
    int cellPosX = 576;
    int cellPosY = 671;
    QPixmap map(maxX, maxY); // Создаем карту для рисования
    QPainter p(&map);

    // Вызываем функцию для рисования препятствий
    drawObstacles(p, maxX, maxY);

    // Остальной код остается без изменений
    for (int i = 0; i < maxX; i++) {
        for (int j = 0; j < maxY; j++) {
            float distance = 0;
            distance = sqrt(pow(abs(cellPosX - i), 2) + pow(abs(cellPosY - j), 2)); // [pix]
            distance *= onePixDistance; // [meters]
            float sigPower = TxPower + antGain - PL(freq, distance);

            // Добавляем расчет затухания при прохождении через препятствие
            float distanceToObstacle = sqrt(pow(abs(cellPosX - i), 2) + pow(abs(cellPosY - j), 2)) * onePixDistance;
            float penetrationLoss = calculatePenetrationLoss (distanceToObstacle, col_wall, material_wall);

            // Вычитаем затухание из основного бюджета канала
            float signalPowerAfterPenetrationLoss = sigPower - penetrationLoss;

            // Остальной код рисования уровня сигнала остается без изменений
            // ...
        }
    }
    p.end();
    scene->addPixmap(map);
    QGraphicsView* view = new QGraphicsView(scene);
    setCentralWidget(view);
}

MainWindow::~MainWindow() {}*/

#include "mainwindow.h"
#include <QtWidgets>
#include <QGroupBox>
#include <QWidget>
#include <cmath>

float MainWindow::PL(float f, float d){
    return 28 + 22 * log10(f) + 20* log10(d);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){

    QGraphicsScene* scene = new QGraphicsScene();
    int maxX = 1000;
    int maxY = 1000;
    double onePixDistance = 10; //[m]
    int TxPower = 10; // [dBm]
    int antGain = 6; // [dBi]
    float freq = 6; // [GHz]
    int cellPosX = 378;
    int cellPosY = 401;
    QPixmap map(maxX, maxY); // создаем карту для рисования
    QPainter p(&map);
    //p.setPen(QColor(255, 0, 0, 255)); // <-- задание цвета
    for(int i = 0; i < maxX; i++){
        for(int j = 0; j < maxY; j++){
            float distance = 0;
            distance = sqrt(pow(abs(cellPosX - i),2) + pow(abs(cellPosY - j),2)); // [pix]
            distance *= onePixDistance; // [meters]
            float sigPower = TxPower + antGain - PL(freq, distance);
            if(sigPower >= -40){
                p.setPen(QColor(255, 0, 0, 255)); // <-- задание цвета
            } else if (sigPower < -40 && sigPower >= -45) {
                p.setPen(QColor(255, 100, 0, 255)); // <-- задание цвета
            } else if (sigPower < -45 && sigPower >= -55) {
                p.setPen(QColor(255, 150, 0, 255)); // <-- задание цвета
            } else if (sigPower < -55 && sigPower >= -60) {
                p.setPen(QColor(255, 200, 0, 255)); // <-- задание цвета
            } else if (sigPower < -60 && sigPower >= -65) {
                p.setPen(QColor(200, 255, 0, 255)); // <-- задание цвета
            } else if (sigPower < -65 && sigPower >= -70) {
                p.setPen(QColor(150, 255, 0, 255)); // <-- задание цвета
            } else if (sigPower < -70 && sigPower >= -75) {
                p.setPen(QColor(100, 255, 0, 255)); // <-- задание цвета
            } else if (sigPower < -75 && sigPower >= -80) {
                p.setPen(QColor(50, 255, 0, 255)); // <-- задание цвета
            } else if (sigPower < -80 && sigPower >= -85) {
                p.setPen(QColor(0, 255, 100, 255)); // <-- задание цвета
            } else if (sigPower < -85 && sigPower >= -90) {
                p.setPen(QColor(0, 255, 150, 255)); // <-- задание цвета
            } else if (sigPower < -90 && sigPower >= -95) {
                p.setPen(QColor(0, 255, 200, 255)); // <-- задание цвета
            } else if (sigPower < -95 && sigPower >= -100) {
                p.setPen(QColor(0, 200, 255, 255)); // <-- задание цвета
            } else if (sigPower < -100 && sigPower >= -105) {
                p.setPen(QColor(0, 150, 255, 255)); // <-- задание цвета
            } else if (sigPower < -105 && sigPower >= -110) {
                p.setPen(QColor(139, 24, 255, 255)); // <-- задание цвета
            } else if (sigPower < -115 && sigPower >= -120) {
                p.setPen(QColor(0, 50, 255, 255)); // <-- задание цвета
            } else if (sigPower < -120 && sigPower >= -125) {
                p.setPen(QColor(116, 24, 255, 255)); // <-- задание цвета
            }
            p.drawPoint(i, j);
        }
    }
    p.end();
    scene->addPixmap(map);
    QGraphicsView* view = new QGraphicsView(scene);
    setCentralWidget(view);

}



MainWindow::~MainWindow()
{
}

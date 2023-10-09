#include "mainwindow.h"
#include <QtWidgets>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), maxX(1000), maxY(1000), onePixDistance(10.0), txPower(10), antGain(6), freq(6.0) {
    scene = new QGraphicsScene();
    QPixmap map(maxX, maxY);
    QPainter painter(&map);

    drawSignalMap(painter);

    painter.end();
    scene->addPixmap(map);
    QGraphicsView *view = new QGraphicsView(scene);
    setCentralWidget(view);
}

/*void MainWindow::drawSignalMap(QPainter &painter) {
    float glassAttenuation = 2.0 + 0.2 * freq;
    float irrGlassAttenuation = 23.0 + 0.3 * freq;
    float concreteAttenuation = 5.0 + 4.0 * freq;
    float woodGypsumAttenuation = 4.85 + 0.12 * freq;

    for (int i = 0; i < maxX; i++) {
        for (int j = 0; j < maxY; j++) {

            float distance = sqrt(pow(abs(378 - i), 2) + pow(abs(401 - j), 2)) * onePixDistance;
            float sigPower = txPower + antGain - pathLoss(distance);

            QColor pixelColor;

            // Рассмотрим разные типы стен и их коэффициенты заглушения
            float wallAttenuation = 0.0;  // Значение по умолчанию (отсутствие стены)

            // Пример: Стеклопакет
            if (isGlassWall(i, j)) {
                wallAttenuation = glassAttenuation;
            }

            // Пример: IRR стекло
            else if (isIrrGlassWall(i, j)) {
                wallAttenuation = irrGlassAttenuation;
            }

            // Пример: Бетон
            else if (isConcreteWall(i, j)) {
                wallAttenuation = concreteAttenuation;
            }

            // Пример: Дерево\гипсокартон
            else if (isWoodOrGypsumWall(i, j)) {
                wallAttenuation = woodGypsumAttenuation;
            }

            // Вычисление сигнальной мощности с учетом коэффициента заглушения стены
            sigPower -= wallAttenuation;

            // Устанавливаем цвет пикселя в зависимости от сигнальной мощности
            if (sigPower >= -40) {
                pixelColor = QColor(255, 0, 0, 255);
            } else if (sigPower >= -45) {
                pixelColor = QColor(255, 100, 0, 255);
            } else if (sigPower >= -50) {
                pixelColor = QColor(255, 100, 0, 255);
            } else if (sigPower >= -55) {
                pixelColor = QColor(255, 150, 0, 255);
            } else if (sigPower >= -60) {
                pixelColor = QColor(255, 200, 0, 255);
            } else if (sigPower >= -65) {
                pixelColor = QColor(255, 255, 0, 255);
            } else if (sigPower >= -70) {
                pixelColor = QColor(200, 255, 0, 255);
            } else if (sigPower >= -75) {
                pixelColor = QColor(150, 255, 0, 255);
            } else if (sigPower >= -80) {
                pixelColor = QColor(100, 255, 0, 255);
            } else if (sigPower >= -85) {
                pixelColor = QColor(50, 255, 0, 255);
            } else if (sigPower >= -90) {
                pixelColor = QColor(0, 255, 0, 255);
            } else if (sigPower >= -95) {
                pixelColor = QColor(0, 255, 50, 255);
            } else if (sigPower >= -100) {
                pixelColor = QColor(0, 255, 100, 255);
            } else if (sigPower >= -105) {
                pixelColor = QColor(0, 255, 150, 255);
            } else if (sigPower >= -110) {
                pixelColor = QColor(0, 255, 200, 255);
            }

            painter.setPen(QPen(pixelColor)); // Используйте QPen
            painter.drawPoint(i, j);
        }
    }
}*/

int** prepztstvie(int x1, int y1, int x2, int y2, int (&matrixR)[4][4]) {
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    int Prep[2][1000];
    int i = 0;
    while(x1 != x2 || y1 != y2){
        Prep[0][i] = x1;
        Prep[1][i] = y1;
        i += 1;
        int error2 = error * 2;
        if(error2 > -deltaY)
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX)
        {
            error += deltaX;
            y1 += signY;
        }
    }
    Prep[0][i] = x2;
    Prep[1][i] = y2;
    return Prep;
}

void drawLine(int x1, int y1, int x2, int y2, int (&matrixR)[4][4]) {
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;


    while(x1 != x2 || y1 != y2)
    {
        for (int i = 0; i < maxX; i++) {
            for (int j = 0; j < maxY; j++) {
                //setPixel(x1, y1);
                int error2 = error * 2;
                if(error2 > -deltaY)
                {
                    error -= deltaY;
                    x1 += signX;
                }
                if(error2 < deltaX)
                {
                    error += deltaX;
                    y1 += signY;
                }
            }
        }
    }

}

void MainWindow::drawSignalMap(QPainter &painter) {
    float glassAttenuation = 2.0 + 0.2 * freq;
    float irrGlassAttenuation = 23.0 + 0.3 * freq;
    float concreteAttenuation = 5.0 + 4.0 * freq;
    float woodGypsumAttenuation = 4.85 + 0.12 * freq;
    int matrix[4][4];
    int (&matrixR)[4][4] = matrix;
    for (int i = 0; i < maxX; i++) {
        for (int j = 0; j < maxY; j++) {
            // Вычисление сигнальной мощности для точки (i, j)
            float distance = sqrt(pow(abs(378 - i), 2) + pow(abs(401 - j), 2)) * onePixDistance;
            // Применение коэффициента заглушения стены (если есть стена)
            float wallAttenuation = 0.0;  // Значение по умолчанию (отсутствие стены)


            // Пример: Стеклопакет
            if (isGlassWall(i, j, matrix)) {
                wallAttenuation = glassAttenuation;
            }

            // Пример: IRR стекло
            else if (isIrrGlassWall(i, j, matrix)) {
                wallAttenuation = irrGlassAttenuation;
            }

            // Пример: Бетон
            else if (isConcreteWall(i, j, matrix)) {
                wallAttenuation = concreteAttenuation;
            }

            // Пример: Дерево\гипсокартон
            else if (isWoodOrGypsumWall(i, j, matrix)) {
                wallAttenuation = woodGypsumAttenuation;
            }
            float sigPower = txPower + antGain - pathLoss(distance)-wallAttenuation;

            /*// Применение коэффициента заглушения стены (если есть стена)
            float wallAttenuation = 0.0;  // Значение по умолчанию (отсутствие стены)

            // Пример: Стеклопакет
            if (isGlassWall(i, j)) {
                wallAttenuation = glassAttenuation;
            }

            // Пример: IRR стекло
            else if (isIrrGlassWall(i, j)) {
                wallAttenuation = irrGlassAttenuation;
            }

            // Пример: Бетон
            else if (isConcreteWall(i, j)) {
                wallAttenuation = concreteAttenuation;
            }

            // Пример: Дерево\гипсокартон
            else if (isWoodOrGypsumWall(i, j)) {
                wallAttenuation = woodGypsumAttenuation;
            }

            // Вычитание коэффициента заглушения от сигнальной мощности
            sigPower -= wallAttenuation;*/

            // Устанавливаем цвет пикселя в зависимости от сигнальной мощности
            QColor pixelColor;

            if (sigPower >= -40) {
                pixelColor = QColor(255, 0, 0, 255);
            } else if (sigPower >= -45) {
                pixelColor = QColor(255, 100, 0, 255);
            } else if (sigPower >= -50) {
                pixelColor = QColor(255, 100, 0, 255);
            } else if (sigPower >= -55) {
                pixelColor = QColor(255, 150, 0, 255);
            } else if (sigPower >= -60) {
                pixelColor = QColor(255, 200, 0, 255);
            } else if (sigPower >= -65) {
                pixelColor = QColor(255, 255, 0, 255);
            } else if (sigPower >= -70) {
                pixelColor = QColor(200, 255, 0, 255);
            } else if (sigPower >= -75) {
                pixelColor = QColor(150, 255, 0, 255);
            } else if (sigPower >= -80) {
                pixelColor = QColor(100, 255, 0, 255);
            } else if (sigPower >= -85) {
                pixelColor = QColor(50, 255, 0, 255);
            } else if (sigPower >= -90) {
                pixelColor = QColor(0, 255, 0, 255);
            } else if (sigPower >= -95) {
                pixelColor = QColor(0, 255, 50, 255);
            } else if (sigPower >= -100) {
                pixelColor = QColor(0, 255, 100, 255);
            } else if (sigPower >= -105) {
                pixelColor = QColor(0, 255, 150, 255);
            } else if (sigPower >= -110) {
                pixelColor = QColor(0, 255, 200, 255);
            }

            painter.setPen(QPen(pixelColor)); // Используйте QPen
            painter.drawPoint(i, j);
        }
    }
}

// Функции для определения типа стены
bool MainWindow::isGlassWall(int x, int y,int (&matrixR)[4][4]) {
    // Задайте координаты и размер области для стеклопакета
    // Например, стеклопакет находится в области от (x1, y1) до (x2, y2)
    int x1 = 126;
    int y1 = 1;
    int x2 = 126;
    int y2 = 50;
    for (int i = 0; i < 1; i++) {
        matrixR[0][1] = x1;
        matrixR[0][2] = y1;
        matrixR[0][3] = x2;
        matrixR[0][4] = y2;
    }
    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

bool MainWindow::isIrrGlassWall(int x, int y,int (&matrixR)[4][4]) {
    // Задайте координаты и размер области для IRR стекла
    // Например, IRR стекло находится в области от (x1, y1) до (x2, y2)
    int x1 = 126;
    int y1 = 100;
    int x2 = 126;
    int y2 = 250;
    for (int i = 1; i < 2; i++) {
        matrixR[1][1] = x1;
        matrixR[1][2] = y1;
        matrixR[1][3] = x2;
        matrixR[1][4] = y2;
    }

    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

bool MainWindow::isConcreteWall(int x, int y,int (&matrixR)[4][4]) {
    // Задайте координаты и размер области для бетона
    // Например, бетон находится в области от (x1, y1) до (x2, y2)
    int x1 = 126;
    int y1 = 300;
    int x2 = 126;
    int y2 = 400;
    for (int i = 2; i < 3; i++) {
        matrixR[2][1] = x1;
        matrixR[2][2] = y1;
        matrixR[2][3] = x2;
        matrixR[2][4] = y2;
    }

    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

bool MainWindow::isWoodOrGypsumWall(int x, int y,int (&matrixR)[4][4]) {
    // Задайте координаты и размер области для дерева или гипсокартона
    // Например, дерево или гипсокартон находятся в области от (x1, y1) до (x2, y2)
    int x1 = 126;
    int y1 = 500;
    int x2 = 126;
    int y2 = 600;
    for (int i = 3; i < 4; i++) {
        matrixR[3][1] = x1;
        matrixR[3][2] = y1;
        matrixR[3][3] = x2;
        matrixR[3][4] = y2;
    }


    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

/*float MainWindow::calculateSignalPower(int x, int y) {
    float distance = sqrt(pow(abs(378 - x), 2) + pow(abs(401 - y), 2)) * onePixDistance;
    return txPower + antGain - pathLoss(distance);
}

float MainWindow::pathLoss(float distance) {
    return 28 + 22 * log10(freq) + 20 * log10(distance);
}*/

MainWindow::~MainWindow() {}


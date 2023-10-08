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

void MainWindow::drawSignalMap(QPainter &painter) {
    float glassAttenuation = 2.0 + 0.2 * freq;
    float irrGlassAttenuation = 23.0 + 0.3 * freq;
    float concreteAttenuation = 5.0 + 4.0 * freq;
    float woodGypsumAttenuation = 4.85 + 0.12 * freq;

    for (int i = 0; i < maxX; i++) {
        for (int j = 0; j < maxY; j++) {
            // Вычисление сигнальной мощности для точки (i, j)
            float distance = sqrt(pow(abs(378 - i), 2) + pow(abs(401 - j), 2)) * onePixDistance;
            // Применение коэффициента заглушения стены (если есть стена)
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
bool MainWindow::isGlassWall(int x, int y) {
    // Задайте координаты и размер области для стеклопакета
    // Например, стеклопакет находится в области от (x1, y1) до (x2, y2)
    int x1 = 126;
    int y1 = 1;
    int x2 = 126;
    int y2 = 50;

    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

bool MainWindow::isIrrGlassWall(int x, int y) {
    // Задайте координаты и размер области для IRR стекла
    // Например, IRR стекло находится в области от (x1, y1) до (x2, y2)
    int x1 = 126;
    int y1 = 100;
    int x2 = 126;
    int y2 = 200;

    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

bool MainWindow::isConcreteWall(int x, int y) {
    // Задайте координаты и размер области для бетона
    // Например, бетон находится в области от (x1, y1) до (x2, y2)
    int x1 = 126;
    int y1 = 300;
    int x2 = 126;
    int y2 = 400;

    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

bool MainWindow::isWoodOrGypsumWall(int x, int y) {
    // Задайте координаты и размер области для дерева или гипсокартона
    // Например, дерево или гипсокартон находятся в области от (x1, y1) до (x2, y2)
    int x1 = 126;
    int y1 = 500;
    int x2 = 126;
    int y2 = 600;

    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

float MainWindow::calculateSignalPower(int x, int y) {
    float distance = sqrt(pow(abs(378 - x), 2) + pow(abs(401 - y), 2)) * onePixDistance;
    return txPower + antGain - pathLoss(distance);
}

float MainWindow::pathLoss(float distance) {
    return 28 + 22 * log10(freq) + 20 * log10(distance);
}

MainWindow::~MainWindow() {}


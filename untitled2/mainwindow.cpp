#include "mainwindow.h"
#include <QtWidgets>
#include <cmath>


    void setupMap();
void MainWindow::setupMap() {
    add_material_to_map(map_obj, 500, 350, 20, 30, (int)type_material::GLASS);
    add_material_to_map(map_obj, 500, 700, 30, 40, (int)type_material::CONCRETE);
    add_material_to_map(map_obj, 700, 500, 50, 80, (int)type_material::WOOD);
}

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

void MainWindow::drawSignalStrength(QPixmap *map); {
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

void MainWindow::createColorMap() {
    int height = 400;
    int width = 150;
    int border = 10;
    QLinearGradient gr(0, 0, 1, height - 2 * border);
    //позже описать цаета

    QPixmap pm(width, height);
    pm.fill(Qt::transparent);
    QPainter pmp(&pm);
    pmp.setBrush(QBrush(gr));
    pmp.setPen(Qt::NoPen);
    pmp.drawRect(border, border, 35, height - 2 * border);
    pmp.setPen(Qt::black);
    int step = (height - 2 * border) / 10;
    for (int i = 0; i < 11; i++) {
        int yPos = i * step + border;
        pmp.drawLine(border, yPos, DRAW_LINE_LENGTH, yPos);
        pmp.drawText(DRAW_LINE_LENGTH + 5, yPos + 2, QString("%1 [dBm]").arg(SIGNAL_COLOR_THRESHOLD - (i * SIGNAL_COLOR_STEP)));
    }

    label_ = new QLabel();
    label_->setPixmap(pm);

    QVBoxLayout *colorMapVBox = new QVBoxLayout;
    colorMapVBox->addWidget(label_);
    gradientGroupBox_->setLayout(colorMapVBox);
}


MainWindow::~MainWindow() {

}

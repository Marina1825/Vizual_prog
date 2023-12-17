#include "mainwindow.h"
#include "Material.h"
#include "Colors.h"
#include "Brezenham.h"
#include "Formuls.h"
#include <QtWidgets>
#include <QGroupBox>
#include <QWidget>
#include <cmath>

#define Pix_to_Meters 10
#define Tx_Power 23
#define Antena_Gain -12
#define frequency 2.5
#define Bs_PosX 500
#define Bs_PosY 500
#define SIGNAL_COLOR_THRESHOLD -44
#define SIGNAL_COLOR_STEP 10
#define DRAW_LINE_LENGTH 55

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      map_obj(new int*[SIZE_MAP_Y])
{
    this->setFixedSize(1200, 1000);

    QGraphicsScene* scene = new QGraphicsScene();
    QPixmap map(SIZE_MAP_X, SIZE_MAP_Y);

    for(int i = 0; i < SIZE_MAP_Y; ++i){
        map_obj[i] = new int[SIZE_MAP_X]{};
    }

    setupMap();
    drawSignalStrength(&map);

    scene->addPixmap(map);
    QGraphicsView* view = new QGraphicsView(scene);
    setCentralWidget(view);
    view->setGeometry(300, 0, SIZE_MAP_X, SIZE_MAP_Y);
    this->layout()->addWidget(view);
    gradientGroupBox_ = new QGroupBox(QStringLiteral("Signal Strength"));
    gradientGroupBox_->setGeometry(50, 100, 200, 700);
    this->layout()->addWidget(gradientGroupBox_);
    createColorMap();
}

void MainWindow::drawSignalStrength(QPixmap* map) {
    QPainter p(map);
    for (int i = 0; i < SIZE_MAP_Y; i++) {
        for (int j = 0; j < SIZE_MAP_X; j++) {
            float distance = calculate(Bs_PosX, i, Bs_PosY, j);
            distance = pix_translate(distance, Pix_to_Meters);
            float Signal_Power = Tx_Power + Antena_Gain - formula(frequency, distance);
            int df = drawBresenhamLine(&p, map_obj, Bs_PosX, Bs_PosY, i, j);
            Signal_Power -= df;
            QColor signalColor(getSignalColor(Signal_Power));
            QPen pen(signalColor);
            p.setPen(pen);
            p.drawPoint(i, j);
        }
    }
    p.end();
}

QString MainWindow::getSignalColor(float signalPower) {
    if (signalPower < SIGNAL_COLOR_THRESHOLD) {
        int index = static_cast<int>((SIGNAL_COLOR_THRESHOLD - signalPower) / SIGNAL_COLOR_STEP);
        switch (index) {
            case 0: return "red";
            case 1: return "orangered";
            case 2: return "orange";
            case 3: return "yellow";
            case 4: return "greenyellow";
            case 5: return "lime";
            case 6: return "mediumseagreen";
            case 7: return "mediumaquamarine";
            case 8: return "royalblue";
            case 9: return "blue";
        }
    }
    return "white";
}

void MainWindow::createColorMap() {
    int height = 400;
    int width = 150;
    int border = 10;
    QLinearGradient gr(0, 0, 1, height - 2 * border);
    gr.setColorAt(1.0f, Qt::blue);
    gr.setColorAt(0.8f, Qt::cyan);
    gr.setColorAt(0.6f, Qt::green);
    gr.setColorAt(0.4f, Qt::yellow);
    gr.setColorAt(0.0f, Qt::red);

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
    for(int i = 0; i < SIZE_MAP_Y; ++i){
        delete[] map_obj[i];
    }
    delete[] map_obj;
}


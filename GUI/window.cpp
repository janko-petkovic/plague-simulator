#include "window.h"
#include "ui_window.h"
#include "window.h"
#include "../Core/Plague.h"
//#include "../Core/Plague.cpp"
#include <string>
#include <QtWidgets>
#include <QtCharts>

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
    _dOI = 2;
    _beta = 0;
    _death.peak = 0;
    _death.distrType.assign("Gaussian");
    _death.finalProb = 0;

    _recov.peak = 0;
    _recov.distrType.assign("Uniform");
    _recov.finalProb = 1;
    _N0 = 100;
    _predictionDays = 10;
    _predictionType = 0;
}

Window::~Window()
{
    delete ui;
}



// days of illness
void Window::set_dOI(int val) { _dOI = val; }
void Window::set_beta(double val) {_beta = val; }

// death status change
void Window::set_deathDistr(int val) {
    if (val==0) _death.distrType.assign("Gaussian");
    else _death.distrType.assign("Uniform");
}

void Window::set_deathPeak(int val) { _death.peak = val; }


// recovery status change
void Window::set_recovDistr(int val) {
    if (val==0) _death.distrType.assign("Gaussian");
    else _death.distrType.assign("Uniform");
}
void Window::set_recovPeak(int val) { _recov.peak = val; }
void Window::set_recovFinalProb(int val) {
    double temp = 0.001*val;
    _recov.finalProb = temp;
    _death.finalProb = 1-temp;
}

// prediction parameters
void Window::set_N0(int val) { _N0 = val; }
void Window::set_predictionDays(int val) { _predictionDays = val; }
void Window::set_predictionType(int val) { _predictionType = val; }


// proviamo intanto a creare un grafico, poi ci pensermo dopo a riempire con dati veri
void Window::simulate() {
    switch(_predictionType) {
        case 0: {
            // plague model deterministic prediction
            break;
        }
        case 1: {
            // plague model stochastic prediction
            break;
        }
    }
    // struttura compatibile con gli output delle previsioni; basta interfacciare
    // i double e i long int
    QStackedBarSeries *series = new QStackedBarSeries();


    vector<double> recovVector(_predictionDays,10);
    vector<double> deadVector(_predictionDays,5);
    vector<double> infectVector(_predictionDays,3);
    QBarSet *infectSet = new QBarSet("Infetti");
    QBarSet *recovSet = new QBarSet("Guariti");
    QBarSet *deadSet = new QBarSet("Deceduti");


    // Constructing sets and series
    for (int i=0; i<_predictionDays; i++) *infectSet << infectVector[i];
    for (int i=0; i<_predictionDays; i++) *recovSet << recovVector[i];
    for (int i=0; i<_predictionDays; i++) *deadSet << deadVector[i];

    series -> append(deadSet);
    series -> append(recovSet);
    series -> append(infectSet);

    // creating the chart, cosmetics and final plotting in new window
    QChart* chart = new QChart();
    chart -> addSeries(series);
    chart -> setTitle("Grafico di prova");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    for (int i=0; i<_predictionDays; i++) categories << QString::number(i);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QMainWindow* outwindow = new QMainWindow;
    outwindow->setCentralWidget(chartView);
    outwindow->resize(900, 600);
    outwindow->show();
}
/*
void Window::simulate() {
    QWidget *wdg = new QWidget;
    wdg->show();
}*/

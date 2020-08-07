#include "window.h"
#include "ui_window.h"
#include "window.h"
#include "dialog.h"
#include "../Core/Plague.h"
#include "../Core/Plague.cpp"

#include <string>
#include <QtWidgets>
#include <QtCharts>
#include <cassert>
#include <iostream>


Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);


    _dOI = 2;
    _beta = 0.5;
    _death.peak = 1;
    _death.distrType.assign("Uniform");
    _death.finalProb = 0;

    _recov.peak = 1;
    _recov.distrType.assign("Uniform");
    _recov.finalProb = 1;
    _N0 = 20;
    _predictionDays = 100;
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
    vector<vector<double>> predictionMatrix;

    PlagueModel model(_dOI, _death, _recov, _beta);
    switch(_predictionType) {
        case 0: {
            predictionMatrix = model.DetPredict(_predictionDays,_N0);
            break;
        }
        case 1: {
            // plague model stochastic prediction
            break;
        }
    }


    Dialog secwindow(this,predictionMatrix,_predictionDays);
    secwindow.resize(1200,900);
    secwindow.setModal(true);
    secwindow.exec();

    for (int k=0; k<_predictionDays; k++) std::cout << predictionMatrix[1][k] << "\t";
    std::cout << std::flush;
    std::cout << _dOI << std::endl;
    std::cout << _beta << std::endl;
    std::cout << _death.peak << std::endl;
    std::cout << _death.distrType << std::endl;
    std::cout << _death.finalProb << std::endl;
    std::cout << _recov.peak << std::endl;
    std::cout << _recov.distrType << std::endl;
    std::cout << _recov.finalProb << std::endl;
    std::cout << _N0 << std::endl;
    std::cout << _predictionDays << std::endl;
    std::cout << _predictionType << std::endl << std::endl << std::flush;
}

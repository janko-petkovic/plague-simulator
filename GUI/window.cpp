#include "window.h"
#include "ui_window.h"
#include "chartwindow.h"
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


    _dOI = 30;
    _beta = 0.05;

    _death.peak = 7;
    _death.distrType.assign("Gaussian");
    _death.finalProb = 0.1;

    _recov.peak = 15;
    _recov.distrType.assign("Gaussian");
    _recov.finalProb = 0.9;
    _N0 = 20;
    _predictionDays = 200;
    _predictionType = 0;
}

Window::~Window()
{
    delete ui;
}



// days of illness setters
void Window::set_dOI(int val) { _dOI = val; }
void Window::set_beta(double val) {_beta = val; }

// death status change setters
void Window::set_deathDistr(int val) {
    if (val==0) _death.distrType.assign("Gaussian");
    else _death.distrType.assign("Uniform");
}
void Window::set_deathPeak(int val) { _death.peak = val; }


// recovery status change setters
void Window::set_recovDistr(int val) {
    if (val==0) _recov.distrType.assign("Gaussian");
    else _recov.distrType.assign("Uniform");
    std::cout << val << " " << _recov.distrType << endl;
}

void Window::set_recovPeak(int val) { _recov.peak = val; }
void Window::set_recovFinalProb(int val) {
    double temp = 0.001*val;
    _recov.finalProb = temp;
    _death.finalProb = 1-temp;
}

// prediction parameters setters
void Window::set_N0(int val) { _N0 = val; }
void Window::set_predictionDays(int val) { _predictionDays = val; }
void Window::set_predictionType(int val) { _predictionType = val; }


// click simulate: calling PlagueModel prediction methods and data plotting
void Window::simulate() {
    vector<vector<double>> predictionMatrix;

    // choosing the prediction: deterministic or stochastic
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

    // constructing the death and recovery rates
    vector<double> deathRate(_predictionDays);
    deathRate[0] = 0;

    vector<double> recovRate(_predictionDays);
    recovRate[0] = 0;

    //vector<double> removed(_predictionDays);
    //std::transform(deathRate.begin(), deathRate.end(),recovRate.begin(),removed.begin(),std::plus<double>());

    for (int i=1; i<_predictionDays; i++) {
        deathRate[i] = predictionMatrix[2][i]/(predictionMatrix[2][i]+predictionMatrix[3][i]);//removed[i];
        recovRate[i] = predictionMatrix[3][i]/(predictionMatrix[2][i]+predictionMatrix[3][i]);//removed[i];
//        std::cout << recovIncr[i] << " " << deadIncr[i];
//        std::cout << predictionMatrix[2][i] << " " << predictionMatrix[3][i] << std::endl << std::flush;
    }


    // creating the vector death and recovery rates
    vector<vector<double>> lineData;
    lineData.push_back(deathRate);
    lineData.push_back(recovRate);


    _chartW = new ChartWindow(this, predictionMatrix,lineData,_predictionDays);
    _chartW->resize(16000,1200);
    _chartW->show();

//    for (int k=0; k<_predictionDays; k++) std::cout << predictionMatrix[1][k] << "\t";
//    std::cout << std::flush;
//    std::cout << _dOI << std::endl;40
//    std::cout << _beta << std::endl;
//    std::cout << _death.peak << std::endl;
//    std::cout << _death.distrType << std::endl;
//    std::cout << _death.finalProb << std::endl;
//    std::cout << _recov.peak << std::endl;
//    std::cout << _recov.distrType << std::endl;
//    std::cout << _recov.finalProb << std::endl;
//    std::cout << _N0 << std::endl;
//    std::cout << _predictionDays << std::endl;
//    std::cout << _predictionType << std::endl << std::endl << std::flush;
}

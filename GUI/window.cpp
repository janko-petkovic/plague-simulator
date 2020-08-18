#include "window.h"
#include "ui_window.h"
#include "chartwindow.h"
#include "../Core/Plague.h"
#include "../Core/Plague.cpp"

#include <QtWidgets>
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;


// Constructor: usual Qt stuff and model parameter initialization
Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);

    // Start-up model parameters
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
    _logging = 0;
}

Window::~Window()
{
	delete _chartW;
    delete ui;
    
    ui = nullptr;
    _chartW = nullptr;
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
void Window::set_logging(bool val) { _logging = val; }


// Click simulate: create a plague model, run the prediction method,
// create the outcome percentages data, draw the two charts
void Window::simulate() {

    // Model istantiation
    PlagueModel model(_dOI, _death, _recov, _beta);

    switch(_predictionType) {

        // Deterministic prediction
        case 0: {

            // infected, dead and recovered data (model.DetPredict())
            vector<vector<double>> predictionMatrix;
            predictionMatrix = model.DetPredict(_predictionDays,_N0);

            // Outcome percentages data: instantiation...
            vector<vector<double>> lineData;
            vector<double> deathFrac(_predictionDays);
            vector<double> recovFrac(_predictionDays);
            deathFrac[0] = 0;
            recovFrac[0] = 0;

            // ...filling...
            for (int i=1; i<_predictionDays; i++) {
                deathFrac[i] = predictionMatrix[2][i]/(predictionMatrix[2][i]+predictionMatrix[3][i]);
                recovFrac[i] = predictionMatrix[3][i]/(predictionMatrix[2][i]+predictionMatrix[3][i]);
            }

            // ...adding to the percentages matrix.
            lineData.push_back(deathFrac);
            lineData.push_back(recovFrac);

            // creating the chartwindow and showing
            _chartW = new ChartWindow(this, predictionMatrix,lineData,_predictionDays);
            _chartW->resize(1600,1200);
            _chartW->show();

            // log predicted data and some final interesting parameters
            if (_logging==1) {
                cout << "\nOUTPUTTING PREDICTED DATA\n";
                cout << "Day \t Cum \t Inf \t Dead \t Rec \t Dead Frac \t Rec frac \n";
                for (int i=0; i<_predictionDays; i++) {
                    cout << i << "\t";
                    cout << predictionMatrix[0][i] << "\t" << predictionMatrix[1][i] << "\t";
                    cout << predictionMatrix[2][i] << "\t" << predictionMatrix[3][i] << "\t";
                    cout << deathFrac[i] << "\t" << recovFrac[i] << endl;
                }

                cout << "\nSome final mean features:\n\n";
                cout << "Case fatality rate: " << predictionMatrix[2][_predictionDays-1]/predictionMatrix[0][_predictionDays-1];
                cout << "\nCase recovery rate: " << predictionMatrix[3][_predictionDays-1]/predictionMatrix[0][_predictionDays-1];
                cout << endl << std::flush;
            }

            break;
        }

        // Stochastic prediction: still to be figured out
        case 1: {
            break;
        }
    }
}

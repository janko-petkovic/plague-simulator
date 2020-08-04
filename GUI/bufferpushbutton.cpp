#include "bufferpushbutton.h"

BufferPushButton::BufferPushButton(QWidget* parent):
    QPushButton(parent) {}




// days of illness
void BufferPushButton::hear_dOI(int val) { _dOI = val; }


// death status change
void BufferPushButton::hear_deathDist(QString str) {
    // riga sfacciatamente copiata da un tipo simpatico di stackoverflow
    _death.distrType = str.toUtf8().constData();
}

void BufferPushButton::hear_deathPeak(int val) { _death.peak = val; }


// recovery status change
void BufferPushButton::hear_recovDist(QString str) {
    // riga sfacciatamente copiata da un tipo simpatico di stackoverflow
    _death.distrType = str.toUtf8().constData();
}
void BufferPushButton::hear_recovPeak(int val) { _recov.peak = val; }
void BufferPushButton::hear_recovFinalProb(int val) {
    double temp = 0.001*val;
    _recov.finalProb = temp;
    _death.finalProb = 1-temp;
}

// prediction parameters
void BufferPushButton::hear_N0(int val) { _N0 = val; }
void BufferPushButton::hear_predictionDays(int val) { _predictionDays = val; }



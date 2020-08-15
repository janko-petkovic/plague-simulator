#include "scaledvaluelabel.h"

ScaledValueLabel::ScaledValueLabel(QWidget* parent):
    QLabel(parent) {};

// used with the death/recovery probability slider as we needed
// to have a triple precision float as output
void ScaledValueLabel::setScaledValue0001(int value) {

    double temp = 0.001*value;
    QString string = QString::number(temp);
    this -> setText(string);
}

// i think this was used before the range limitation in the
// sliders
void ScaledValueLabel::setValueMinus1(int val) {

    int temp = val - 1;
    QString string = QString::number(temp);
    this -> setText(string);
}

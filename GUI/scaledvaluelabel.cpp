#include "scaledvaluelabel.h"

ScaledValueLabel::ScaledValueLabel(QWidget* parent):
    QLabel(parent) {};

void ScaledValueLabel::setScaledValue0001(int value) {
    double temp = 0.001*value;
    QString string = QString::number(temp);
    this -> setText(string);
}

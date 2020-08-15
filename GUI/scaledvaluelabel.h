// Auxiliary label class with some custom methods

#ifndef SCALEDVALUELABEL_H
#define SCALEDVALUELABEL_H
#include <QLabel>


class ScaledValueLabel : public QLabel
{
    Q_OBJECT

public:    
    ScaledValueLabel(QWidget *parent = nullptr): QLabel(parent) {};

public slots:

    // used with the death/recovery probability input label as we needed
    // to have a triple precision float as input
    void setScaledValue0001(int value) {
        double temp = 0.001*value;
        QString string = QString::number(temp);
        this -> setText(string);
    };

    // used for the max label on the peak sliders
    void setValueMinus1(int val) {
        int temp = val - 1;
        QString string = QString::number(temp);
        this -> setText(string);
    };

};

#endif // SCALEDVALUELABEL_H

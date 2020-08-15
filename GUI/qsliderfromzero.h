// Custom slider class used in the peak sliders to exclude
// day 0 and the last days from the possible inputs (the peak cannot
// fall on the edge of the time interval per definition)

#ifndef QSLIDERFROMZERO_H
#define QSLIDERFROMZERO_H
#include <QSlider>

class QSliderFromZero : public QSlider {

Q_OBJECT

public:
    QSliderFromZero(QWidget *parent = nullptr): QSlider(parent) {};

public slots:
    void setMaximum(int max) { this -> setRange(1,max-1); }
};

#endif

#include <qsliderfromzero.h>

QSliderFromZero::QSliderFromZero(QWidget *parent):
    QSlider(parent) {}

// Given input max set the slider range from 1 to max-1
void QSliderFromZero::setMaximum(int max) {
    this->setRange(1,max-1);
}

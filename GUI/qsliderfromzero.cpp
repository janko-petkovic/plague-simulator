#include <qsliderfromzero.h>
#include <QMainWindow>

QSliderFromZero::QSliderFromZero(QWidget *parent):
    QSlider(parent) {}

void QSliderFromZero::setMaximum(int max) {
    this->setRange(0,max);
}

#ifndef QSLIDERFROMZERO_H
#define QSLIDERFROMZERO_H
#include <QSlider>

class QSliderFromZero : public QSlider {

Q_OBJECT

public:
    QSliderFromZero(QWidget *parent = nullptr);

public slots:
    void setMaximum(int);
};

#endif

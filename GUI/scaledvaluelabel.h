#ifndef SCALEDVALUELABEL_H
#define SCALEDVALUELABEL_H
#include <QLabel>


class ScaledValueLabel : public QLabel
{

    Q_OBJECT

public:    
    ScaledValueLabel(QWidget *parent = nullptr);

public slots:
    void setScaledValue0001(int);

};

#endif // SCALEDVALUELABEL_H

#ifndef BUFFERPUSHBUTTON_H
#define BUFFERPUSHBUTTON_H

#include <QPushButton>
#include "../Core/Plague.h"

class BufferPushButton : public QPushButton
{
    Q_OBJECT

    statusChange _recov;
    statusChange _death;
    int _dOI;
    int _N0;
    int _predictionDays;

public:
    BufferPushButton(QWidget* parent=nullptr);

public slots:
    void hear_recovPeak(int);
    void hear_recovFinalProb(int); // questo modifica anche deathFinalProb
    void hear_recovDist(QString);

    void hear_deathPeak(int);
    void hear_deathDist(QString);
    void hear_dOI(int);
    void hear_N0(int);
    void hear_predictionDays(int);
};

#endif // BUFFERPUSHBUTTON_H

#ifndef WINDOW_H
#define WINDOW_H

#include "../Core/Plague.h"
#include "chartwindow.h"
#include <QMainWindow>
#include <QVariant>



QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE




class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

public slots:
    void set_recovPeak(int);
    void set_recovFinalProb(int); // questo modifica anche deathFinalProb
    void set_recovDistr(int);

    void set_deathPeak(int);
    void set_deathDistr(int);
    void set_dOI(int);
    void set_beta(double);
    void set_N0(int);
    void set_predictionDays(int);
    void set_predictionType(int);

    void simulate();

private:
    Ui::Window *ui;
    ChartWindow* _chartW;

    statusChange _recov;
    statusChange _death;
    double _beta;
    int _dOI;
    int _N0;
    int _predictionDays;
    int _predictionType;
};
#endif // WINDOW_H

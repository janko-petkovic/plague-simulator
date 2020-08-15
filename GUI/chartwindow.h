#ifndef CHARTWINDOW_H
#define CHARTWINDOW_H


#include <QMainWindow>
#include <vector>

using std::vector;

namespace Ui {
    class ChartWindow;
}

class ChartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChartWindow(QWidget *parent, vector<vector<double>>&, vector<vector<double>>&, int);
    ~ChartWindow();

private:
    Ui::ChartWindow *ui;
};

#endif // CHARTWINDOW_H

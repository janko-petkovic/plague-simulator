#include "chartwindow.h"
#include "ui_chartwindow.h"
#include "drawchart.cpp"

#include <QtCharts>
#include <vector>

using std::vector;

ChartWindow::ChartWindow(QWidget *parent, vector<vector<double>>& stackedData,
                         vector<vector<double>>& lineData, int predictionDays) :
    QMainWindow(parent),
    ui(new Ui::ChartWindow)
{
    ui->setupUi(this);

    // drawing the graphs
    QChart* stackedChart = StackedChart(stackedData,predictionDays);
    QChart* lineChart = LineChart(lineData,predictionDays);

    // Setting up the chart window layout
    QChartView* stackedView = new QChartView(stackedChart);
    QChartView* lineView = new QChartView(lineChart);
    QFrame* centralFrame = new QFrame();
    QVBoxLayout* myLayout = new QVBoxLayout;

    myLayout->addWidget(stackedView);
    myLayout->addWidget(lineView);

    stackedView->setRenderHint(QPainter::Antialiasing);
    lineView->setRenderHint(QPainter::Antialiasing);

    centralFrame->setLayout(myLayout);
    setCentralWidget(centralFrame);
}

ChartWindow::~ChartWindow()
{
    delete ui;
}

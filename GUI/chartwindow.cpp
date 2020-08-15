#include "chartwindow.h"
#include "ui_chartwindow.h"
#include "chartutils.cpp"


// Constructor: draw the two charts
ChartWindow::ChartWindow(QWidget *parent, vector<vector<double>>& stackedData,
                         vector<vector<double>>& lineData, int predictionDays) :
    QMainWindow(parent),
    ui(new Ui::ChartWindow)
{
    ui->setupUi(this);

    // Charts instantiation and definition
    QChart* stackedChart = StackedChart(stackedData,predictionDays);
    QChart* lineChart = LineChart(lineData,predictionDays);

    // Setting up the chart view
    QChartView* stackedView = new QChartView(stackedChart);
    QChartView* lineView = new QChartView(lineChart);
    stackedView->setRenderHint(QPainter::Antialiasing);
    lineView->setRenderHint(QPainter::Antialiasing);

    // putting together the display matrioska:
    // View >> Layout >> Frame >> Window
    QFrame* centralFrame = new QFrame();
    QVBoxLayout* myLayout = new QVBoxLayout;

    myLayout->addWidget(stackedView);
    myLayout->addWidget(lineView);
    centralFrame->setLayout(myLayout);
    setCentralWidget(centralFrame);

}

// destructor: delete the self pointer
ChartWindow::~ChartWindow()
{
    delete ui;
}

#include "dialog.h"
#include "ui_dialog.h"

#include <QtCharts>
#include <vector>

using std::vector;

Dialog::Dialog(QWidget *parent, vector<vector<double>> predictionMatrix, int predictionDays) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QStackedBarSeries *series = new QStackedBarSeries();

    QBarSet *infectSet = new QBarSet("Infetti");
    QBarSet *recovSet = new QBarSet("Guariti");
    QBarSet *deadSet = new QBarSet("Deceduti");


    // Constructing sets and series
    for (int i=0; i<predictionDays; i++) *infectSet << predictionMatrix[1][i];
    for (int i=0; i<predictionDays; i++) *deadSet << predictionMatrix[2][i];
    for (int i=0; i<predictionDays; i++) *recovSet << predictionMatrix[3][i];

    series -> append(deadSet);
    series -> append(recovSet);
    series -> append(infectSet);

    // creating the chart, cosmetics and final plotting in second window
    QChart* chart = new QChart();
    chart -> addSeries(series);
    chart -> setTitle("Grafico di prova");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    for (int i=0; i<predictionDays; i++) categories << QString::number(i);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    ui->layout_chart->addWidget(chartView);
    chartView->setRenderHint(QPainter::Antialiasing);

}

Dialog::~Dialog()
{
    delete ui;
}

#include <QtCharts>
#include <vector>
#include <iostream>

using std::vector;


QChart* StackedChart(const vector<vector<double>>& data, const int predictionDays) {

    QStackedBarSeries *series = new QStackedBarSeries();

    QBarSet *infectSet = new QBarSet("Infetti");
    QBarSet *recovSet = new QBarSet("Guariti");
    QBarSet *deadSet = new QBarSet("Deceduti");
    QStringList categories;

    // Constructing sets and series
    for (int i=0; i<predictionDays; i++) {
        *infectSet << data[1][i];
        *deadSet << data[2][i];
        *recovSet << data[3][i];
        categories << QString::number(i);
    }

    series -> append(infectSet);
    series -> append(deadSet);
    series -> append(recovSet);

    QChart* PAYLOAD = new QChart();
    PAYLOAD -> addSeries(series);


    // Skin care and nail polish:

    QColor color;
    QFont font;

    // Bar colors
    color.setNamedColor("#FFD8C684");
    infectSet -> setColor(QColor(color));
    color.setNamedColor("#DD0C695D");
    recovSet -> setColor(QColor(color));
    color.setNamedColor("#DDDA5526");
    deadSet -> setColor(QColor(color));

    // Title
    font.setPixelSize(17);
    PAYLOAD -> setTitleFont(font);
    PAYLOAD -> setTitleBrush(Qt::black);
    PAYLOAD -> setTitle("INFETTI ATTIVI, GUARITI, DECEDUTI");

    // Axes
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    QValueAxis *axisY = new QValueAxis();

    axisX -> append(categories);
    font.setPixelSize(13);
    axisX -> setTitleFont(font);
    axisX -> setTitleText("Giorno");

    axisY -> setTitleFont(font);
    axisY -> setTitleText("Occorrenze");

    PAYLOAD->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    PAYLOAD->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    return PAYLOAD;
}


// overload of the function above without explicit prediction days
QChart* StackedChart(const vector<vector<double>>& data) {
    int predictionDays = data.size();
    return StackedChart(data,predictionDays);
}



QChart* LineChart(const vector<vector<double>>& data, const int predictionDays) {

    QLineSeries *deadSeries = new QLineSeries();
    deadSeries -> setName("Deceduti");
    QLineSeries *recovSeries = new QLineSeries();
    recovSeries -> setName("Guariti");

    // Constructing sets and series
    for (int i=0; i<predictionDays; i++) {
        deadSeries -> append(i,data[0][i]);
        recovSeries -> append(i,data[1][i]);
    }



    // creating the chart, cosmetics and final plotting in second window
    QFont font;
    QColor color;

    QChart* PAYLOAD = new QChart();
    PAYLOAD -> addSeries(deadSeries);
    PAYLOAD -> addSeries(recovSeries);

    QValueAxis *axisX = new QValueAxis();
    font.setPixelSize(13);
    axisX->setTitleFont(font);
    axisX->setTitleText("Giorni");
    PAYLOAD -> addAxis(axisX, Qt::AlignBottom);
    deadSeries -> attachAxis(axisX);
    recovSeries -> attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    font.setPixelSize(13);
    axisY->setTitleFont(font);
    axisY->setTitleText("%");
    PAYLOAD -> addAxis(axisY, Qt::AlignLeft);
    deadSeries -> attachAxis(axisY);
    recovSeries -> attachAxis(axisY);



    font.setPixelSize(17);
    PAYLOAD -> setTitleFont(font);
    PAYLOAD -> setTitle("OUTCOME DEI PAZIENTI RIMOSSI");

    color.setNamedColor("#DD0C695D");
    recovSeries -> setColor(QColor(color));
    color.setNamedColor("#DDDA5526");
    deadSeries -> setColor(QColor(color));

    return PAYLOAD;
}


// like before, overload of the function above without explicit prediction days
QChart* LineChart(const vector<vector<double>>& data) {
    int predictionDays = data.size();
    return LineChart(data,predictionDays);
}

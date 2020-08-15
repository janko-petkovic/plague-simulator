#ifndef CHART_UTILS_CPP
#define CHART_UTILS_CPP

#include <QtCharts>
#include <vector>

using std::vector;



// Stacked bar chart creation. We templatize to be able to call this
// same function from the StochasticPrediction() as well - not yet implemented
// (note how we templatize this method and not the LineChart one)
template<class C>
QChart* StackedChart(const vector<vector<C>>& data, const int predictionDays) {

    // Series istantiation
    QStackedBarSeries *series = new QStackedBarSeries();

    // Set istantiation and filling (we add the XAxis Categories as well for practicality)
    QBarSet *infectSet = new QBarSet("Infetti");
    QBarSet *recovSet = new QBarSet("Guariti");
    QBarSet *deadSet = new QBarSet("Deceduti");
    QStringList categories;

    for (int i=0; i<predictionDays; i++) {
        *infectSet << data[1][i];
        *deadSet << data[2][i];
        *recovSet << data[3][i];
        categories << QString::number(i);
    }

    // Appending the three sets to the series
    series -> append(infectSet);
    series -> append(deadSet);
    series -> append(recovSet);

    // Create chart and append series to it
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

    // Axes:
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    QValueAxis *axisY = new QValueAxis();

    axisX -> append(categories);
    font.setPixelSize(13);
    axisX -> setTitleFont(font);
    axisX -> setTitleText("Giorno");

    axisY -> setTitleFont(font);
    axisY -> setTitleText("Occorrenze");

    // axis attachment and return
    PAYLOAD->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    PAYLOAD->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    return PAYLOAD;
}


// Overload of the function above without explicit prediction days (just in case)
template<class C>
QChart* StackedChart(const vector<vector<C>>& data) {

    // recover the prediction days from the data size
    int predictionDays = data.size();

    // call overload above and return
    return StackedChart(data,predictionDays);
}


// Line chart creation
QChart* LineChart(const vector<vector<double>>& data, const int predictionDays) {

    // Istantiate the two series (dead and recovered percentage)
    QLineSeries *deadSeries = new QLineSeries();
    deadSeries -> setName("Deceduti");
    QLineSeries *recovSeries = new QLineSeries();
    recovSeries -> setName("Guariti");

    // Filling the two series
    for (int i=0; i<predictionDays; i++) {
        deadSeries -> append(i,data[0][i]);
        recovSeries -> append(i,data[1][i]);
    }

    // Chart creation and series appending
    QChart* PAYLOAD = new QChart();
    PAYLOAD -> addSeries(deadSeries);
    PAYLOAD -> addSeries(recovSeries);


    // Beauty lotions and make up
    QFont font;
    QColor color;

    // Title
    font.setPixelSize(17);
    PAYLOAD -> setTitleFont(font);
    PAYLOAD -> setTitle("OUTCOME DEI PAZIENTI RIMOSSI");

    // Series color
    color.setNamedColor("#DD0C695D");
    recovSeries -> setColor(QColor(color));
    color.setNamedColor("#DDDA5526");
    deadSeries -> setColor(QColor(color));

    // Axes
    font.setPixelSize(13);
    PAYLOAD -> createDefaultAxes();
    PAYLOAD -> axes()[0]->setTitleFont(font);
    PAYLOAD -> axes()[0]->setTitleText("Giorno");
    PAYLOAD -> axes()[1]->setTitleFont(font);
    PAYLOAD -> axes()[1]->setTitleText("%");

    return PAYLOAD;
}


// like before, overload of the function above without the prediction days argument
QChart* LineChart(const vector<vector<double>>& data) {
    // recover prediction days
    int predictionDays = data.size();

    // call above and return
    return LineChart(data,predictionDays);
}


#endif

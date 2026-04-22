#ifndef TOURISTCHARTDIALOG_H
#define TOURISTCHARTDIALOG_H

#include <QDialog>
#include <QtCharts>
#include "datastorage.h"

class TouristChartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TouristChartDialog(DataStorage* storage, QWidget* parent = nullptr);

    ~TouristChartDialog();

private:
    void setupChart(DataStorage* storage);
};

#endif // TOURISTCHARTDIALOG_H

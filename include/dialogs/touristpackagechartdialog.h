#ifndef TOURISTPACKAGECHARTDIALOG_H
#define TOURISTPACKAGECHARTDIALOG_H

#include <QDialog>
#include <QtCharts>
#include "datastorage.h"

QT_CHARTS_USE_NAMESPACE

class TouristPackageChartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TouristPackageChartDialog(DataStorage* storage, QWidget* parent = nullptr);

    ~TouristPackageChartDialog();

private:
    void setupChart(DataStorage* storage);
};

#endif // TOURISTPACKAGECHARTDIALOG_H

#ifndef DESTINATIONCHARTDIALOG_H
#define DESTINATIONCHARTDIALOG_H

#include <QDialog>
#include <QtCharts>
#include "datastorage.h"

class DestinationChartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DestinationChartDialog(DataStorage* storage, QWidget* parent = nullptr);

    ~DestinationChartDialog();

private:
    void setupChart(DataStorage* storage);
};

#endif // DESTINATIONCHARTDIALOG_H

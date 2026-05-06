#ifndef DESTINATIONCHARTDIALOG_H
#define DESTINATIONCHARTDIALOG_H

#include "datastorage.h"
#include "dialogs/basechartdialog.h"

/**
 * @class DestinationChartDialog
 * @brief Круговая диаграмма распределения отелей по количеству звёзд.
 * @extends BaseChartDialog
 */
class DestinationChartDialog : public BaseChartDialog {
    Q_OBJECT

public:
    /**
     * @brief Конструктор. Сразу строит диаграмму на основе хранилища.
     */
    explicit DestinationChartDialog(DataStorage *storage, QWidget *parent = nullptr);

    /**
     * @override BaseChartDialog::~BaseChartDialog
     */
    ~DestinationChartDialog() override = default;

private:
    /**
     * @brief Подсчитывает статистику и строит QPieSeries.
     */
    void setupChart(DataStorage *storage);
};

#endif // DESTINATIONCHARTDIALOG_H

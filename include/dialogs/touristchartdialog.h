#ifndef TOURISTCHARTDIALOG_H
#define TOURISTCHARTDIALOG_H

#include "datastorage.h"
#include "dialogs/basechartdialog.h"

/**
 * @class TouristChartDialog
 * @brief Круговая диаграмма распределения туристов по полу.
 * @extends BaseChartDialog
 */
class TouristChartDialog : public BaseChartDialog {
    Q_OBJECT

public:
    /**
     * @brief Конструктор. Сразу строит диаграмму.
     */
    explicit TouristChartDialog(DataStorage *storage, QWidget *parent = nullptr);

    /**
     * @override BaseChartDialog::~BaseChartDialog
     */
    ~TouristChartDialog() override = default;

private:
    /**
     * @brief Подсчитывает кол-во по полу и строит QPieSeries.
     */
    void setupChart(DataStorage *storage);
};

#endif // TOURISTCHARTDIALOG_H

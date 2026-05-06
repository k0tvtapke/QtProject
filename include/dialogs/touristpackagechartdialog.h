#ifndef TOURISTPACKAGECHARTDIALOG_H
#define TOURISTPACKAGECHARTDIALOG_H

#include "datastorage.h"
#include "dialogs/basechartdialog.h"

/**
 * @class TouristPackageChartDialog
 * @brief Столбчатая диаграмма ТОП-10 самых популярных направлений.
 * @extends BaseChartDialog
 */
class TouristPackageChartDialog : public BaseChartDialog {
    Q_OBJECT

public:
    /**
     * @brief Конструктор. Сразу строит диаграмму.
     */
    explicit TouristPackageChartDialog(DataStorage *storage, QWidget *parent = nullptr);

    /**
     * @override BaseChartDialog::~BaseChartDialog
     */
    ~TouristPackageChartDialog() override = default;

private:
    /**
     * @brief Агрегирует продажи по направлениям и строит горизонтальные бары.
     */
    void setupChart(DataStorage *storage);
};

#endif // TOURISTPACKAGECHARTDIALOG_H

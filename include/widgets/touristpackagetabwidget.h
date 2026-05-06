#ifndef TOURISTPACKAGETABWIDGET_H
#define TOURISTPACKAGETABWIDGET_H

#include "datastorage.h"
#include "widgets/basetabwidget.h"

/**
 * @class TouristPackageTabWidget
 * @brief Вкладка «Путёвки».
 * @extends BaseTabWidget
 */
class TouristPackageTabWidget : public BaseTabWidget {
    Q_OBJECT

public:
    /**
     * @brief Конструктор. Подключает `TouristPackageTableModel`.
     */
    explicit TouristPackageTabWidget(DataStorage *storage, QWidget *parent = nullptr);

private:
    DataStorage *m_dataStorage;     ///< Хранилище данных (без владения).

    /**
     * @brief Открыть диалог добавления новой путёвки.
     * @override BaseTabWidget::on_addEntryButton_clicked
     */
    void on_addEntryButton_clicked() override;

    /**
     * @brief Открыть диалог редактирования выбранной путёвки.
     * @override BaseTabWidget::on_editEntryButton_clicked
     */
    void on_editEntryButton_clicked() override;

    /**
     * @brief Логически удалить выбранную путёвку (с подтверждением).
     * @override BaseTabWidget::on_deleteEntryButton_clicked
     */
    void on_deleteEntryButton_clicked() override;

    /**
     * @brief Сформировать текстовый отчёт по выбранной путёвке.
     * @override BaseTabWidget::on_createReportButton_clicked
     */
    void on_createReportButton_clicked() override;

private slots:
    /**
     * @brief Открыть диалог столбчатой диаграммы популярных направлений.
     */
    void onShowChartButtonClicked();
};

#endif // TOURISTPACKAGETABWIDGET_H

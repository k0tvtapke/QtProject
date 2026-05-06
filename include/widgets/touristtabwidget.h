#ifndef TOURISTTABWIDGET_H
#define TOURISTTABWIDGET_H

#include "datastorage.h"
#include "widgets/basetabwidget.h"

/**
 * @class TouristTabWidget
 * @brief Вкладка «Туристы».
 * @extends BaseTabWidget
 */
class TouristTabWidget : public BaseTabWidget {
    Q_OBJECT

public:
    /**
     * @brief Конструктор. Подключает `TouristTableModel`.
     */
    explicit TouristTabWidget(DataStorage *storage, QWidget *parent = nullptr);

private:
    DataStorage *m_dataStorage;     ///< Хранилище данных (без владения).

    /**
     * @brief Открыть диалог добавления нового туриста.
     * @override BaseTabWidget::on_addEntryButton_clicked
     */
    void on_addEntryButton_clicked() override;

    /**
     * @brief Открыть диалог редактирования выбранного туриста.
     * @override BaseTabWidget::on_editEntryButton_clicked
     */
    void on_editEntryButton_clicked() override;

    /**
     * @brief Логически удалить выбранного туриста (с подтверждением).
     * @override BaseTabWidget::on_deleteEntryButton_clicked
     */
    void on_deleteEntryButton_clicked() override;

    /**
     * @brief Сформировать текстовый отчёт по выбранному туристу.
     * @override BaseTabWidget::on_createReportButton_clicked
     */
    void on_createReportButton_clicked() override;

private slots:
    /**
     * @brief Открыть диалог диаграммы соотношения полов туристов.
     */
    void onShowChartButtonClicked();
};

#endif // TOURISTTABWIDGET_H

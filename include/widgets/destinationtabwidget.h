#ifndef DESTINATIONTABWIDGET_H
#define DESTINATIONTABWIDGET_H

#include "datastorage.h"
#include "widgets/basetabwidget.h"

/**
 * @class DestinationTabWidget
 * @brief Вкладка «Направления».
 * @extends BaseTabWidget
 */
class DestinationTabWidget : public BaseTabWidget {
    Q_OBJECT

public:
    /**
     * @brief Конструктор. Подключает `DestinationTableModel` к таблице.
     * @param storage Указатель на in-memory БД.
     * @param parent Родительский виджет.
     */
    explicit DestinationTabWidget(DataStorage *storage, QWidget *parent = nullptr);

protected:
    DataStorage *m_dataStorage;     ///< Хранилище данных (без владения).

    /**
     * @brief Открыть диалог добавления нового направления.
     * @override BaseTabWidget::on_addEntryButton_clicked
     */
    void on_addEntryButton_clicked() override;

    /**
     * @brief Открыть диалог редактирования выбранного направления.
     * @override BaseTabWidget::on_editEntryButton_clicked
     */
    void on_editEntryButton_clicked() override;

    /**
     * @brief Логически удалить выбранное направление (с подтверждением).
     * @override BaseTabWidget::on_deleteEntryButton_clicked
     */
    void on_deleteEntryButton_clicked() override;

    /**
     * @brief Сформировать текстовый отчёт по выбранному направлению.
     * @override BaseTabWidget::on_createReportButton_clicked
     */
    void on_createReportButton_clicked() override;

private slots:
    /**
     * @brief Открыть диалог круговой диаграммы по звёздам отелей.
     */
    void onShowChartButtonClicked();
};

#endif // DESTINATIONTABWIDGET_H

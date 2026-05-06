#ifndef BASETABWIDGET_H
#define BASETABWIDGET_H

#include "models/basetablemodel.h"

#include <QItemSelection>
#include <QSortFilterProxyModel>
#include <QWidget>
#include <optional>

namespace Ui {
    class BaseTabWidget;
}

/**
 * @class BaseTabWidget
 * @brief Общий базовый виджет вкладки таблицы.
 * @details Содержит таблицу записей, кнопки add/edit/delete/report/chart,
 *          фильтр по столбцу и сортировку (через `QSortFilterProxyModel`).
 *          Конкретные слоты add/edit/delete/createReport — чисто виртуальные.
 *
 * @extends QWidget
 */
class BaseTabWidget : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Конструктор.
     * @param tableModel Конкретная табличная модель (BaseTabWidget берёт владение).
     * @param parent Родительский виджет.
     */
    explicit BaseTabWidget(BaseTableModel *tableModel, QWidget *parent = nullptr);

    /**
     * @brief Деструктор. Удаляет ui, модель и proxy-модель.
     * @override QWidget::~QWidget
     */
    ~BaseTabWidget() override;

    /**
     * @brief Принудительно перезагружает таблицу (вызывает `beginResetModel`).
     */
    void reloadTable();

    /**
     * @brief Подгоняет ширину столбцов под содержимое.
     */
    void resizeTable();

protected:
    Ui::BaseTabWidget *ui;                          ///< Сгенерированный uic-объект.
    BaseTableModel *m_tableModel;                   ///< Источник данных.
    QSortFilterProxyModel *m_sortFilterModel;       ///< Сортировка/фильтрация поверх модели.

    /**
     * @brief Возвращает реальный индекс выбранной строки.
     * @return std::nullopt, если выбора нет.
     */
    std::optional<size_t> currentSelectedRealIndex();

    /**
     * @brief Показывает диалог подтверждения удаления.
     * @return true если пользователь нажал «Да».
     */
    bool confirmDelete();

    /**
     * @brief Стандартное действие после изменения данных: reloadTable + resizeTable.
     */
    void afterMutation();

protected slots:
    /**
     * @brief Открыть диалог добавления записи.
     * @pure
     */
    virtual void on_addEntryButton_clicked() = 0;

    /**
     * @brief Открыть диалог редактирования выбранной записи.
     * @pure
     */
    virtual void on_editEntryButton_clicked() = 0;

    /**
     * @brief Удалить выбранную запись (с подтверждением).
     * @pure
     */
    virtual void on_deleteEntryButton_clicked() = 0;

    /**
     * @brief Сформировать текстовый отчёт по выбранной записи.
     * @pure
     */
    virtual void on_createReportButton_clicked() = 0;

private slots:
    /**
     * @brief Реакция на смену выделения — включает/выключает edit/delete/report-кнопки.
     */
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    /**
     * @brief Смена столбца поиска.
     * @param index Индекс столбца в комбобоксе.
     */
    void on_searchFilterComboBox_currentIndexChanged(int index);

    /**
     * @brief Реакция на изменение поискового запроса.
     */
    void on_searchFilterLineEdit_textChanged(const QString &text);

    /**
     * @brief Сбросить поисковый фильтр.
     */
    void on_resetFilterPushButton_clicked();
};

#endif // BASETABWIDGET_H

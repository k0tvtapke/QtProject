#ifndef ENTRYSELECTIONDIALOG_H
#define ENTRYSELECTIONDIALOG_H

#include "models/basetablemodel.h"

#include <QDialog>
#include <QItemSelection>

namespace Ui {
    class EntrySelectionDialog;
}

/**
 * @class EntrySelectionDialog
 * @brief Диалог выбора одной или нескольких записей из таблицы.
 * @details Используется при создании путёвки для выбора туристов
 *          (множественный выбор) и направления (одиночный выбор).
 *
 * @extends QDialog
 */
class EntrySelectionDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Конструктор.
     * @param isSingleSelection true — одиночный выбор, false — множественный.
     * @param tableModel Источник данных (без владения).
     */
    explicit EntrySelectionDialog(bool isSingleSelection, BaseTableModel *tableModel, QWidget *parent = nullptr);

    /**
     * @override QDialog::~QDialog
     */
    ~EntrySelectionDialog();

    /**
     * @brief Получить ID выбранных записей (множественный режим).
     * @warning Должен вызываться только при `isSingleSelection == false`.
     */
    QList<quint32> getChosenIndexes();

    /**
     * @brief Получить ID единственной выбранной записи.
     * @warning Должен вызываться только при `isSingleSelection == true`.
     */
    quint32 getChosenIndex();

private:
    Ui::EntrySelectionDialog *ui;        ///< Сгенерированный uic-объект.

    bool m_isSingleSelection;            ///< Режим выбора.
    BaseTableModel *m_tableModel;        ///< Источник данных.

private slots:
    /**
     * @brief Включает submit-кнопку при наличии выбора.
     */
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    /**
     * @brief Подтверждение выбора.
     */
    void on_addDestinationSelectionButton_clicked();

    /**
     * @brief Отмена выбора.
     */
    void on_cancelDestinationSelectionButton_clicked();
};

#endif // ENTRYSELECTIONDIALOG_H

#ifndef NEWDESTINATIONENTRYDIALOG_H
#define NEWDESTINATIONENTRYDIALOG_H

#include "datastorage.h"
#include "dialogs/baseentrydialog.h"

namespace Ui {
    class NewDestinationEntryDialog;
}

/**
 * @class NewDestinationEntryDialog
 * @brief Диалог добавления/редактирования направления.
 * @extends BaseEntryDialog
 */
class NewDestinationEntryDialog : public BaseEntryDialog {
    Q_OBJECT

public:
    /**
     * @brief Конструктор для добавления нового направления.
     * @param id Будущий ID, отображаемый в read-only поле.
     */
    explicit NewDestinationEntryDialog(size_t id, QWidget *parent = nullptr);

    /**
     * @brief Конструктор для редактирования существующего направления.
     * @param destinationEntry Указатель на запись (без владения).
     */
    explicit NewDestinationEntryDialog(DestinationEntry *destinationEntry, QWidget *parent = nullptr);

    /**
     * @brief Деструктор. Освобождает запись в режиме «новой».
     * @override BaseEntryDialog::~BaseEntryDialog
     */
    ~NewDestinationEntryDialog() override;

    /**
     * @brief Получить заполненные данные.
     * @return Копия `DestinationEntry`.
     */
    DestinationEntry getDestinationEntry() const;

private slots:
    /**
     * @brief Подтверждение ввода — копирует значения в запись и закрывает диалог.
     */
    void on_addEntryButton_clicked();

    /**
     * @brief Отмена — закрывает диалог без сохранения.
     */
    void on_cancelButton_clicked();

private:
    /**
     * @brief Регистрация валидаторов и submit-кнопки в `BaseEntryDialog`.
     */
    void setupValidators();

    bool isNew;                               ///< true для режима добавления.
    DestinationEntry *m_destination_entry;    ///< Указатель на редактируемую запись.

    Ui::NewDestinationEntryDialog *ui;        ///< Сгенерированный uic-объект.
};

#endif // NEWDESTINATIONENTRYDIALOG_H

#ifndef NEWTOURISTENTRYDIALOG_H
#define NEWTOURISTENTRYDIALOG_H

#include "datastorage.h"
#include "dialogs/baseentrydialog.h"

namespace Ui {
    class NewTouristEntryDialog;
}

/**
 * @class NewTouristEntryDialog
 * @brief Диалог добавления/редактирования туриста.
 * @extends BaseEntryDialog
 */
class NewTouristEntryDialog : public BaseEntryDialog {
    Q_OBJECT

public:
    /**
     * @brief Конструктор для добавления нового туриста.
     * @param id Будущий ID.
     */
    explicit NewTouristEntryDialog(size_t id, QWidget *parent = nullptr);

    /**
     * @brief Конструктор для редактирования существующего туриста.
     * @param touristEntry Указатель на запись (без владения).
     */
    explicit NewTouristEntryDialog(TouristEntry *touristEntry, QWidget *parent = nullptr);

    /**
     * @override BaseEntryDialog::~BaseEntryDialog
     */
    ~NewTouristEntryDialog() override;

    /**
     * @brief Получить заполненные данные.
     */
    TouristEntry getTouristEntry() const;

private slots:
    /**
     * @brief Подтверждение ввода.
     */
    void on_addEntryButton_clicked();

    /**
     * @brief Отмена.
     */
    void on_cancelButton_clicked();

private:
    /**
     * @brief Регистрация валидаторов и submit-кнопки.
     */
    void setupValidators();

    bool isNew;                          ///< true — режим добавления.
    TouristEntry *m_touristEntry;        ///< Указатель на редактируемую запись.

    Ui::NewTouristEntryDialog *ui;       ///< Сгенерированный uic-объект.
};

#endif // NEWTOURISTENTRYDIALOG_H

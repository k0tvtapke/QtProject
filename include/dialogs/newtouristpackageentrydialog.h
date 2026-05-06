#ifndef NEWTOURISTPACKAGEENTRYDIALOG_H
#define NEWTOURISTPACKAGEENTRYDIALOG_H

#include "datastorage.h"
#include "dialogs/baseentrydialog.h"

namespace Ui {
    class NewTouristPackageEntryDialog;
}

/**
 * @class NewTouristPackageEntryDialog
 * @brief Диалог добавления/редактирования путёвки.
 * @details Помимо текстовых валидаторов проверяет, что выбран хотя бы
 *          один турист и направление (`additionalAcceptanceCheck`).
 *
 * @extends BaseEntryDialog
 */
class NewTouristPackageEntryDialog : public BaseEntryDialog {
    Q_OBJECT

public:
    /**
     * @brief Конструктор для добавления новой путёвки.
     * @param id Будущий ID.
     * @param dataStorage Хранилище для выбора туристов и направлений.
     */
    explicit NewTouristPackageEntryDialog(size_t id, DataStorage *dataStorage, QWidget *parent = nullptr);

    /**
     * @brief Конструктор для редактирования существующей путёвки.
     */
    explicit NewTouristPackageEntryDialog(TouristPackageEntry *touristPackageEntry, DataStorage *dataStorage,
                                          QWidget *parent = nullptr);

    /**
     * @override BaseEntryDialog::~BaseEntryDialog
     */
    ~NewTouristPackageEntryDialog() override;

    /**
     * @brief Получить заполненные данные.
     * @throw std::bad_optional_access Если ID направления не выбран.
     */
    TouristPackageEntry getTouristPackageEntry() const;

protected:
    /**
     * @brief Дополнительная проверка: должны быть выбраны туристы и направление.
     * @override BaseEntryDialog::additionalAcceptanceCheck
     */
    bool additionalAcceptanceCheck() const override;

private slots:
    /**
     * @brief Подтверждение ввода.
     */
    void on_addEntryButton_clicked();

    /**
     * @brief Отмена.
     */
    void on_cancelButton_clicked();

    /**
     * @brief Открыть диалог выбора туристов (`EntrySelectionDialog`).
     */
    void on_chooseTouristButton_clicked();

    /**
     * @brief Открыть диалог выбора направления.
     */
    void on_chooseDestinationButton_clicked();

private:
    /**
     * @brief Обновить ярлык со списком выбранных туристов.
     */
    void refreshChosenTouristsLabel();

    /**
     * @brief Обновить ярлык с информацией о выбранном направлении.
     */
    void refreshChosenDestinationLabel();

    bool isNew;                                     ///< true — режим добавления.
    DataStorage *m_dataStorage;                     ///< Хранилище (без владения).

    QList<uint32_t> m_touristsIds;                  ///< Выбранные туристы.
    std::optional<uint32_t> m_destinationId;        ///< Выбранное направление.
    TouristPackageEntry *m_touristPackageEntry;     ///< Указатель на редактируемую запись.

    Ui::NewTouristPackageEntryDialog *ui;           ///< Сгенерированный uic-объект.
};

#endif // NEWTOURISTPACKAGEENTRYDIALOG_H

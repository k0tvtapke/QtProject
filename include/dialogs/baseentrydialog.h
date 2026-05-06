#ifndef BASEENTRYDIALOG_H
#define BASEENTRYDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QList>
#include <QPushButton>
#include <QRegularExpression>
#include <QString>

/**
 * @class BaseEntryDialog
 * @brief Базовый класс диалогов добавления/редактирования записей.
 * @details
 *   Предоставляет общий механизм soft-валидации полей `QLineEdit` без блокировки ввода:
 *     - регистрируются валидируемые поля (`registerValidatedField`);
 *     - регистрируется кнопка-подтверждения (`setSubmitButton`);
 *     - при изменении любого поля вызывается `revalidate()`, которая
 *       подсвечивает невалидные поля красной рамкой и тултипом, а кнопка
 *       блокируется до приведения формы в валидное состояние.
 *   Подклассы могут переопределить `additionalAcceptanceCheck()` для дополнительных
 *   проверок (например, наличие выбранных туристов в путёвке).
 *
 * @extends QDialog
 */
class BaseEntryDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Конструктор.
     */
    explicit BaseEntryDialog(QWidget *parent = nullptr);

    /**
     * @brief Деструктор по умолчанию.
     * @override QDialog::~QDialog
     */
    ~BaseEntryDialog() override = default;

protected:
    /**
     * @brief Параметры одного зарегистрированного поля.
     */
    struct ValidatedField {
        QLineEdit *edit;       ///< Редактируемое поле.
        QString fieldLabel;    ///< Человекочитаемое имя поля для тултипов.
        QString tooltipOk;     ///< Тултип в нормальном (валидном) состоянии.
    };

    /**
     * @brief Зарегистрировать поле для soft-валидации.
     * @param edit Указатель на `QLineEdit`.
     * @param re Регулярное выражение, которому должно соответствовать значение.
     * @param fieldLabel Человекочитаемое имя поля (для тултипа об ошибке).
     * @param tooltipOk Тултип, отображаемый при валидном значении.
     */
    void registerValidatedField(QLineEdit *edit,
                                const QRegularExpression &re,
                                const QString &fieldLabel,
                                const QString &tooltipOk);

    /**
     * @brief Указать кнопку, которая блокируется при невалидной форме.
     * @param button Кнопка подтверждения (например, «Добавить запись»).
     */
    void setSubmitButton(QPushButton *button);

    /**
     * @brief Принудительно перепроверить состояние всех полей и кнопки.
     */
    void revalidate();

    /**
     * @brief Точка расширения для дополнительных проверок формы.
     * @return По умолчанию true. Переопределите, чтобы заблокировать submit
     *         при отсутствии выбора связанных сущностей и т.п.
     * @virtual
     */
    virtual bool additionalAcceptanceCheck() const;

private slots:
    /**
     * @brief Слот, подключённый к `QLineEdit::textChanged` каждого зарегистрированного поля.
     */
    void onLineEditChanged();

private:
    QList<ValidatedField> m_fields;         ///< Зарегистрированные валидируемые поля.
    QPushButton *m_submitButton = nullptr;  ///< Кнопка submit (без владения).
};

#endif // BASEENTRYDIALOG_H

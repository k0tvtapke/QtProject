#ifndef SOFTREGEXVALIDATOR_H
#define SOFTREGEXVALIDATOR_H

#include <QRegularExpression>
#include <QRegularExpressionValidator>

/**
 * @class SoftRegexValidator
 * @brief Регекс-валидатор, никогда не возвращающий состояние `Invalid`.
 * @details
 *   Стандартный `QRegularExpressionValidator` блокирует ввод символов, при которых
 *   текст никогда не может стать валидным (`QValidator::Invalid`), что заставляет
 *   `QLineEdit` отклонять ввод. Этот класс наследуется и переопределяет
 *   `validate()`: значение `Invalid` подменяется на `Intermediate`, ввод
 *   остаётся свободным, но `QLineEdit::hasAcceptableInput()` остаётся надёжным
 *   индикатором валидности (true только при `Acceptable`).
 *
 * @extends QRegularExpressionValidator
 */
class SoftRegexValidator : public QRegularExpressionValidator {
    Q_OBJECT

public:
    /**
     * @brief Пустой конструктор.
     */
    explicit SoftRegexValidator(QObject *parent = nullptr);

    /**
     * @brief Конструктор с регекспом.
     */
    explicit SoftRegexValidator(const QRegularExpression &re, QObject *parent = nullptr);

    /**
     * @override QValidator::validate
     * @return Никогда не вернёт `Invalid`; вместо этого вернёт `Intermediate`.
     */
    QValidator::State validate(QString &input, int &pos) const override;
};

#endif // SOFTREGEXVALIDATOR_H

#include "dialogs/baseentrydialog.h"

#include "util/softregexvalidator.h"

BaseEntryDialog::BaseEntryDialog(QWidget *parent)
    : QDialog(parent) {
}

void BaseEntryDialog::registerValidatedField(QLineEdit *edit,
                                             const QRegularExpression &re,
                                             const QString &fieldLabel,
                                             const QString &tooltipOk) {
    edit->setValidator(new SoftRegexValidator(re, this));
    edit->setToolTip(tooltipOk);
    m_fields.append({edit, fieldLabel, tooltipOk});

    connect(edit, &QLineEdit::textChanged, this, &BaseEntryDialog::onLineEditChanged);
}

void BaseEntryDialog::setSubmitButton(QPushButton *button) {
    m_submitButton = button;
}

bool BaseEntryDialog::additionalAcceptanceCheck() const {
    return true;
}

void BaseEntryDialog::onLineEditChanged() {
    revalidate();
}

void BaseEntryDialog::revalidate() {
    bool allValid = true;

    for (const auto &field : m_fields) {
        if (field.edit->hasAcceptableInput()) {
            field.edit->setStyleSheet("");
            field.edit->setToolTip(field.tooltipOk);
        } else {
            field.edit->setStyleSheet("border: 1px solid red;");
            field.edit->setToolTip(
                QString("Поле «%1» заполнено некорректно. ").arg(field.fieldLabel) + field.tooltipOk);
            allValid = false;
        }
    }

    if (!m_submitButton) return;

    if (allValid && additionalAcceptanceCheck()) {
        m_submitButton->setEnabled(true);
        m_submitButton->setToolTip("");
    } else {
        m_submitButton->setDisabled(true);
        m_submitButton->setToolTip("Заполните корректно все поля");
    }
}

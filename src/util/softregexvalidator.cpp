#include "util/softregexvalidator.h"

SoftRegexValidator::SoftRegexValidator(QObject *parent)
    : QRegularExpressionValidator(parent) {
}

SoftRegexValidator::SoftRegexValidator(const QRegularExpression &re, QObject *parent)
    : QRegularExpressionValidator(re, parent) {
}

QValidator::State SoftRegexValidator::validate(QString &input, int &pos) const {
    QValidator::State state = QRegularExpressionValidator::validate(input, pos);
    if (state == QValidator::Invalid) {
        return QValidator::Intermediate;
    }
    return state;
}

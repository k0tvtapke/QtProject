#include "util/reportformatters.h"
#include "util/enumlabels.h"

namespace ReportFormatters {

QString indentStr(int indent) {
    return QString(indent, QChar(' '));
}

QString formatTouristBlock(const TouristEntry &entry, int indent) {
    const QString pad = indentStr(indent);
    QString result;
    result += pad + QString("-Имя: %1\n").arg(entry.m_firstName);
    result += pad + QString("-Фамилия: %1\n").arg(entry.m_lastName);
    if (!entry.m_surname.isEmpty()) {
        result += pad + QString("-Отчество: %1\n").arg(entry.m_surname);
    }
    result += pad + QString("-Пол: %1\n").arg(kGenders[static_cast<size_t>(entry.m_gender)]);
    result += pad + QString("-Дата рождения: %1\n").arg(entry.m_birthDate.toString("dd.MM.yyyy"));
    return result;
}

QString formatDestinationBlock(const DestinationEntry &entry, int indent) {
    const QString pad = indentStr(indent);
    QString result;
    result += pad + QString("Данные о направлении (ID %1):\n").arg(entry.m_id.value());
    result += pad + QString("    -Страна: %1\n").arg(entry.m_country);
    result += pad + QString("    -Город: %1\n").arg(entry.m_city);
    result += pad + QString("    -Базовая цена: %1\n").arg(entry.m_basePrice);
    result += pad + QString("    -Тип питания: %1\n").arg(kFoodTypes[static_cast<size_t>(entry.m_foodType)]);
    result += pad + QString("    -Кол-во звезд отеля: %1\n").arg(entry.m_hotelStars);
    return result;
}

}

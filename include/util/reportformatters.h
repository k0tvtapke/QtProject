#ifndef REPORTFORMATTERS_H
#define REPORTFORMATTERS_H

#include "datastorage.h"

#include <QString>

/**
 * @namespace ReportFormatters
 * @brief Функции форматирования записей в текстовые блоки отчётов.
 */
namespace ReportFormatters {

/**
 * @brief Возвращает строку из `indent` пробелов (отступ).
 * @param indent Количество пробелов.
 */
QString indentStr(int indent);

/**
 * @brief Сформировать многострочный блок с данными о туристе.
 * @param entry Турист.
 * @param indent Глобальный отступ слева (в пробелах).
 * @return Строка, оканчивающаяся переводом строки.
 */
QString formatTouristBlock(const TouristEntry &entry, int indent = 0);

/**
 * @brief Сформировать многострочный блок с данными о направлении.
 * @param entry Направление.
 * @param indent Глобальный отступ слева.
 * @throw std::bad_optional_access Если у `entry` нет ID.
 */
QString formatDestinationBlock(const DestinationEntry &entry, int indent = 0);

}

#endif // REPORTFORMATTERS_H

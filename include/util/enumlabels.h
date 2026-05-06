#ifndef ENUMLABELS_H
#define ENUMLABELS_H

#include <QString>

/**
 * @brief Человекочитаемые подписи для `FoodType`.
 * @details Индекс соответствует значению `static_cast<size_t>(FoodType::*)`.
 */
inline const QString kFoodTypes[]{
    "Без питания",
    "Только завтрак",
    "Полупансион",
    "Полный пансион",
    "Все включено",
    "Ультра все включено"
};

/**
 * @brief Человекочитаемые подписи для `Gender`.
 */
inline const QString kGenders[]{
    "Мужской",
    "Женский"
};

#endif // ENUMLABELS_H

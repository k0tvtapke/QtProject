#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QDate>
#include <QFile>
#include <QList>
#include <optional>

/**
 * @brief Сериализация std::optional<quint32> в QDataStream.
 * @details Записывает признак наличия (bool), затем — само значение (если есть).
 */
QDataStream &operator<<(QDataStream &out, const std::optional<quint32> &opt);

/**
 * @brief Десериализация std::optional<quint32> из QDataStream.
 * @throw QDataStream::ReadCorruptData при повреждённом потоке.
 */
QDataStream &operator>>(QDataStream &in, std::optional<quint32> &opt);

/**
 * @enum Gender
 * @brief Пол туриста.
 */
enum class Gender {
    MALE = 0,   ///< Мужской.
    FEMALE = 1  ///< Женский.
};

QDataStream &operator<<(QDataStream &out, const Gender &g);
QDataStream &operator>>(QDataStream &in, Gender &g);

/**
 * @enum FoodType
 * @brief Уровень питания в отеле.
 */
enum class FoodType {
    RO = 0,  ///< Без питания (Room Only).
    BB = 1,  ///< Только завтрак (Bed & Breakfast).
    HB = 2,  ///< Полупансион (Half Board).
    FB = 3,  ///< Полный пансион (Full Board).
    AI = 4,  ///< Все включено (All Inclusive).
    UAI = 5  ///< Ультра все включено (Ultra All Inclusive).
};

QDataStream &operator<<(QDataStream &out, const FoodType &f);
QDataStream &operator>>(QDataStream &in, FoodType &f);

/**
 * @struct DestinationEntry
 * @brief Запись о туристическом направлении.
 * @details Хранит уникальный ID, страну, город, базовую цену, тип питания,
 *          количество звёзд и флаг логического удаления.
 */
struct DestinationEntry {
    std::optional<quint32> m_id;  ///< Уникальный идентификатор (выставляется DataStorage).
    QString m_country;            ///< Страна.
    QString m_city;               ///< Город.
    double m_basePrice;           ///< Базовая цена (>= 0).
    FoodType m_foodType;          ///< Уровень питания.
    quint8 m_hotelStars;          ///< Кол-во звёзд отеля (1..5).
    bool m_isRemoved = false;     ///< Флаг логического удаления.

    /**
     * @brief Конструктор с инициализацией всех бизнес-полей.
     * @param country Страна.
     * @param city Город.
     * @param basePrice Базовая цена (>= 0).
     * @param foodType Уровень питания.
     * @param hotelStars Кол-во звёзд (1..5).
     */
    DestinationEntry(QString country,
                     QString city,
                     double basePrice,
                     FoodType foodType,
                     quint8 hotelStars);

    /**
     * @brief Конструктор по умолчанию для (де)сериализации.
     */
    DestinationEntry() = default;
};

QDataStream &operator<<(QDataStream &out, const DestinationEntry &d);
QDataStream &operator>>(QDataStream &in, DestinationEntry &d);

/**
 * @struct TouristEntry
 * @brief Запись о туристе.
 * @details Хранит ФИО (отчество необязательно), пол, дату рождения и флаг
 *          логического удаления.
 */
struct TouristEntry {
    std::optional<quint32> m_id;  ///< Уникальный идентификатор.
    QString m_firstName;          ///< Имя.
    QString m_lastName;           ///< Фамилия.
    QString m_surname = "";       ///< Отчество (может быть пустым).
    Gender m_gender;              ///< Пол.
    QDate m_birthDate;            ///< Дата рождения.
    bool m_isRemoved = false;     ///< Флаг логического удаления.

    /**
     * @brief Конструктор без отчества.
     * @param firstName Имя.
     * @param lastName Фамилия.
     * @param gender Пол.
     * @param birthDate Дата рождения.
     */
    TouristEntry(QString firstName,
                 QString lastName,
                 Gender gender,
                 QDate birthDate);

    /**
     * @brief Конструктор с отчеством.
     * @param firstName Имя.
     * @param lastName Фамилия.
     * @param surname Отчество.
     * @param gender Пол.
     * @param birthDate Дата рождения.
     */
    TouristEntry(QString firstName,
                 QString lastName,
                 QString surname,
                 Gender gender,
                 QDate birthDate);

    /**
     * @brief Конструктор по умолчанию для (де)сериализации.
     */
    TouristEntry() = default;
};

QDataStream &operator<<(QDataStream &out, const TouristEntry &t);
QDataStream &operator>>(QDataStream &in, TouristEntry &t);

/**
 * @struct TouristPackageEntry
 * @brief Запись о туристической путёвке.
 * @details Связывает список туристов с направлением, фиксирует дату вылета,
 *          длительность и итоговую стоимость.
 */
struct TouristPackageEntry {
    std::optional<quint32> m_id;  ///< Уникальный идентификатор.
    QList<quint32> m_touristsIds; ///< Идентификаторы участников.
    quint32 m_destinationId;      ///< Идентификатор направления.
    QDate m_arrivalDate;          ///< Дата вылета.
    quint32 m_duration;           ///< Длительность (в днях).
    double m_finalPrice;          ///< Итоговая цена.
    bool m_isRemoved = false;     ///< Флаг логического удаления.

    /**
     * @brief Конструктор с инициализацией бизнес-полей.
     * @param touristsIds Идентификаторы туристов.
     * @param destinationId Идентификатор направления.
     * @param arrivalDate Дата вылета.
     * @param duration Длительность (в днях).
     * @param finalPrice Итоговая цена (>= 0).
     */
    TouristPackageEntry(QList<quint32> touristsIds,
                        quint32 destinationId,
                        QDate arrivalDate,
                        quint32 duration,
                        double finalPrice);

    /**
     * @brief Конструктор по умолчанию для (де)сериализации.
     */
    TouristPackageEntry() = default;
};

QDataStream &operator<<(QDataStream &out, const TouristPackageEntry &p);
QDataStream &operator>>(QDataStream &in, TouristPackageEntry &p);

/**
 * @class DataStorage
 * @brief Контейнер in-memory БД из трёх коллекций (направления / туристы / путёвки)
 *        с возможностью (де)сериализации в .bin-файл.
 * @details
 *   - Удаление записей — логическое (по флагу `m_isRemoved`), без сдвига индексов,
 *     чтобы сохранить связи через ID между путёвками, туристами и направлениями.
 *   - Поверх «реальных» индексов вычисляются «view»-индексы — позиции среди живых записей.
 */
class DataStorage {
public:
    QList<DestinationEntry> m_destinationEntries;          ///< Все направления (вкл. удалённые).
    QList<TouristEntry> m_touristEntries;                  ///< Все туристы (вкл. удалённых).
    QList<TouristPackageEntry> m_touristPackageEntries;    ///< Все путёвки (вкл. удалённые).

    /**
     * @brief Добавить новое направление.
     * @param new_entry Запись (поле `m_id` будет проставлено автоматически).
     */
    void addDestinationEntry(DestinationEntry new_entry);

    /**
     * @brief Добавить нового туриста.
     * @param new_entry Запись (поле `m_id` будет проставлено автоматически).
     */
    void addTouristEntry(TouristEntry new_entry);

    /**
     * @brief Добавить новую путёвку.
     * @param new_entry Запись (поле `m_id` будет проставлено автоматически).
     */
    void addTouristPackageEntry(TouristPackageEntry new_entry);

    /**
     * @brief Логически удалить направление по реальному индексу.
     * @param idx Реальный индекс в `m_destinationEntries`.
     * @warning Должен указывать на «живую» запись.
     */
    void deleteDestinationEntry(const size_t idx);

    /**
     * @brief Логически удалить туриста по реальному индексу.
     * @param idx Реальный индекс в `m_touristEntries`.
     */
    void deleteTouristEntry(const size_t idx);

    /**
     * @brief Логически удалить путёвку по реальному индексу.
     * @param idx Реальный индекс в `m_touristPackageEntries`.
     */
    void deleteTouristPackageEntry(const size_t idx);

    /**
     * @brief Преобразовать view-индекс направления в реальный.
     * @param view_idx Позиция среди не удалённых записей.
     * @return Реальный индекс в `m_destinationEntries`.
     * @throw std::out_of_range Если `view_idx` выходит за пределы.
     */
    size_t destinationEntryViewIndexToRealIndex(const size_t view_idx);

    /**
     * @brief Преобразовать view-индекс туриста в реальный.
     * @throw std::out_of_range Если `view_idx` выходит за пределы.
     */
    size_t touristEntryViewIndexToRealIndex(const size_t view_idx);

    /**
     * @brief Преобразовать view-индекс путёвки в реальный.
     * @throw std::out_of_range Если `view_idx` выходит за пределы.
     */
    size_t touristPackageEntryViewIndexToRealIndex(const size_t view_idx);

    /**
     * @brief Кол-во направлений в «представлении» (без удалённых).
     */
    size_t getDestinationEntriesViewCount();

    /**
     * @brief Кол-во туристов в «представлении» (без удалённых).
     */
    size_t getTouristEntriesViewCount();

    /**
     * @brief Кол-во путёвок в «представлении» (без удалённых).
     */
    size_t getTouristPackageEntriesViewCount();

    /**
     * @brief Сохранить состояние БД в бинарный файл.
     * @param filename Путь к файлу.
     * @return true при успехе, false если файл не открылся для записи.
     */
    bool saveToFile(const QString &filename) const;

    /**
     * @brief Загрузить состояние БД из бинарного файла.
     * @param filename Путь к файлу.
     * @return true при успехе и валидном потоке, false при ошибке.
     */
    bool loadFromFile(const QString &filename);
};

#endif // DATASTORAGE_H

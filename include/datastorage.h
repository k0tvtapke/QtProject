#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QString>
#include <QDate>
#include <QList>
#include <QFile>

constexpr int kDestinationEntryColumnCount = 6;
constexpr int kTouristEntryColumnCount = 6;
constexpr int kTouristPackageEntryColumnCount = 6;

QDataStream &operator<<(QDataStream &out, const std::optional<quint32> &opt);

QDataStream &operator>>(QDataStream &in, std::optional<quint32> &opt);

enum class Gender {
    MALE = 0,
    FEMALE = 1
};

QDataStream &operator<<(QDataStream &out, const Gender &g);

QDataStream &operator>>(QDataStream &in, Gender &g);

enum class FoodType {
    RO = 0, // Room Only
    BB = 1, // Bed & Breakfast
    HB = 2, // Half Board
    FB = 3, // Full Board
    AI = 4, // All Inclusive
    UAI = 5 // Ultra All Inclusive
};

QDataStream &operator<<(QDataStream &out, const FoodType &f);

QDataStream &operator>>(QDataStream &in, FoodType &f);

struct DestinationEntry {
    std::optional<quint32> m_id;
    QString m_country;
    QString m_city;
    qreal m_basePrice;
    FoodType m_foodType;
    quint8 m_hotelStars;
    bool m_isRemoved = false;

    DestinationEntry(QString country,
                     QString city,
                     qreal basePrice,
                     FoodType foodType,
                     quint8 hotelStars);

    DestinationEntry() = default;
};

QDataStream &operator<<(QDataStream &out, const DestinationEntry &d);

QDataStream &operator>>(QDataStream &in, DestinationEntry &d);

struct TouristEntry {
    std::optional<quint32> m_id;
    QString m_firstName;
    QString m_lastName;
    QString m_surname = "";
    Gender m_gender;
    QDate m_birthDate;
    bool m_isRemoved = false;

    TouristEntry(QString firstName,
                 QString lastName,
                 Gender gender,
                 QDate birthDate);

    TouristEntry(QString firstName,
                 QString lastName,
                 QString surname,
                 Gender gender,
                 QDate birthDate);

    TouristEntry() = default;
};

QDataStream &operator<<(QDataStream &out, const TouristEntry &t);

QDataStream &operator>>(QDataStream &in, TouristEntry &t);

struct TouristPackageEntry {
    std::optional<quint32> m_id;
    QList<quint32> m_touristsIds;
    quint32 m_destinationId;
    QDate m_arrivalDate;
    quint32 m_duration;
    qreal m_finalPrice;
    bool m_isRemoved = false;

    TouristPackageEntry(QList<quint32> touristsIds,
                        quint32 destinationId,
                        QDate arrivalDate,
                        quint32 duration,
                        qreal finalPrice);

    TouristPackageEntry() = default;
};

QDataStream &operator<<(QDataStream &out, const TouristPackageEntry &p);

QDataStream &operator>>(QDataStream &in, TouristPackageEntry &p);

class DataStorage {
public:
    QList<DestinationEntry> m_destinationEntries;
    QList<TouristEntry> m_touristEntries;
    QList<TouristPackageEntry> m_touristPackageEntries;

    void addDestinationEntry(DestinationEntry new_entry);

    void addTouristEntry(TouristEntry new_entry);

    void addTouristPackageEntry(TouristPackageEntry new_entry);

    void deleteDestinationEntry(const size_t idx);

    void deleteTouristEntry(const size_t idx);

    void deleteTouristPackageEntry(const size_t idx);

    bool saveToFile(const QString &filename) const;

    bool loadFromFile(const QString &filename);
};

#endif // DATASTORAGE_H

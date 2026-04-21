#include "datastorage.h"
#include <QDataStream>
#include <cassert>

// Конструкторы
DestinationEntry::DestinationEntry(QString country,
                                   QString city,
                                   double basePrice,
                                   FoodType foodType,
                                   quint8 hotelStars) : m_country(country),
    m_city(city),
    m_basePrice(basePrice),
    m_foodType(foodType),
    m_hotelStars(hotelStars) {
}

TouristEntry::TouristEntry(QString firstName,
                           QString lastName,
                           Gender gender,
                           QDate birthDate) : m_firstName(firstName),
    m_lastName(lastName),
    m_gender(gender),
    m_birthDate(birthDate) {
}

TouristEntry::TouristEntry(QString firstName,
                           QString lastName,
                           QString surname,
                           Gender gender,
                           QDate birthDate) : m_firstName(firstName),
    m_lastName(lastName),
    m_surname(surname),
    m_gender(gender),
    m_birthDate(birthDate) {
}

TouristPackageEntry::TouristPackageEntry(QList<quint32> touristsIds,
                                         quint32 destinationId,
                                         QDate arrivalDate,
                                         quint32 duration,
                                         double finalPrice) : m_touristsIds(touristsIds),
    m_destinationId(destinationId),
    m_arrivalDate(arrivalDate),
    m_duration(duration),
    m_finalPrice(finalPrice) {
}

// Операторы для enum
QDataStream &operator<<(QDataStream &out, const Gender &g) {
    return out << static_cast<int>(g);
}

QDataStream &operator>>(QDataStream &in, Gender &g) {
    int v;
    in >> v;
    g = static_cast<Gender>(v);
    return in;
}

QDataStream &operator<<(QDataStream &out, const FoodType &f) {
    return out << static_cast<int>(f);
}

QDataStream &operator>>(QDataStream &in, FoodType &f) {
    int v;
    in >> v;
    f = static_cast<FoodType>(v);
    return in;
}

// Операторы для std::optional (если нужен)
QDataStream &operator<<(QDataStream &out, const std::optional<quint32> &opt) {
    if (opt.has_value()) {
        out << true << *opt;
    } else {
        out << false;
    }
    return out;
}

QDataStream &operator>>(QDataStream &in, std::optional<quint32> &opt) {
    bool hasValue;
    in >> hasValue;
    if (hasValue) {
        quint32 val;
        in >> val;
        opt = val;
    } else {
        opt = std::nullopt;
    }
    return in;
}

// Операторы для DestinationEntry
QDataStream &operator<<(QDataStream &out, const DestinationEntry &d) {
    out << d.m_id
        << d.m_country
        << d.m_city
        << d.m_basePrice
        << d.m_foodType
        << d.m_hotelStars
        << d.m_isRemoved;
    return out;
}

QDataStream &operator>>(QDataStream &in, DestinationEntry &d) {
    in >> d.m_id
        >> d.m_country
        >> d.m_city
        >> d.m_basePrice
        >> d.m_foodType
        >> d.m_hotelStars
        >> d.m_isRemoved;
    return in;
}

// Операторы для TouristEntry
QDataStream &operator<<(QDataStream &out, const TouristEntry &t) {
    out << t.m_id
        << t.m_firstName
        << t.m_lastName
        << t.m_surname
        << t.m_gender
        << t.m_birthDate
        << t.m_isRemoved;
    return out;
}

QDataStream &operator>>(QDataStream &in, TouristEntry &t) {
    in >> t.m_id
        >> t.m_firstName
        >> t.m_lastName
        >> t.m_surname
        >> t.m_gender
        >> t.m_birthDate
        >> t.m_isRemoved;
    return in;
}

// Операторы для TouristPackageEntry
QDataStream &operator<<(QDataStream &out, const TouristPackageEntry &p) {
    out << p.m_id
        << p.m_touristsIds
        << p.m_destinationId
        << p.m_arrivalDate
        << p.m_duration
        << p.m_finalPrice
        << p.m_isRemoved;
    return out;
}

QDataStream &operator>>(QDataStream &in, TouristPackageEntry &p) {
    in >> p.m_id
        >> p.m_touristsIds
        >> p.m_destinationId
        >> p.m_arrivalDate
        >> p.m_duration
        >> p.m_finalPrice
        >> p.m_isRemoved;
    return in;
}

// Методы DataStorage
void DataStorage::addDestinationEntry(DestinationEntry new_entry) {
    new_entry.m_id = static_cast<quint32>(m_destinationEntries.size());
    m_destinationEntries.append(new_entry);
}

void DataStorage::addTouristEntry(TouristEntry new_entry) {
    new_entry.m_id = static_cast<quint32>(m_touristEntries.size());
    m_touristEntries.append(new_entry);
}

void DataStorage::addTouristPackageEntry(TouristPackageEntry new_entry) {
    new_entry.m_id = static_cast<quint32>(m_touristPackageEntries.size());
    m_touristPackageEntries.append(new_entry);
}

void DataStorage::deleteDestinationEntry(const size_t idx) {
    assert(m_destinationEntries.size() > idx);
    assert(!m_destinationEntries[idx].m_isRemoved);
    m_destinationEntries[idx].m_isRemoved = true;
}

void DataStorage::deleteTouristEntry(const size_t idx) {
    assert(m_touristEntries.size() > idx);
    assert(!m_touristEntries[idx].m_isRemoved);
    m_touristEntries[idx].m_isRemoved = true;
}

void DataStorage::deleteTouristPackageEntry(const size_t idx) {
    assert(m_touristPackageEntries.size() > idx);
    assert(!m_touristPackageEntries[idx].m_isRemoved);
    m_touristPackageEntries[idx].m_isRemoved = true;
}

size_t DataStorage::destinationEntryViewIndexToRealIndex(const size_t view_idx) {
    assert(m_destinationEntries.size() > view_idx);
    size_t visibleCount = 0;
    for (int i = 0; i < m_destinationEntries.size(); ++i) {
        if (!m_destinationEntries[i].m_isRemoved) {
            if (visibleCount == view_idx) {
                return static_cast<size_t>(i);
            }
            ++visibleCount;
        }
    }
    throw std::out_of_range("Variable view_idx out of range");
}

size_t DataStorage::touristEntryViewIndexToRealIndex(const size_t view_idx) {
    assert(m_touristEntries.size() > view_idx);
    size_t visibleCount = 0;
    for (int i = 0; i < m_touristEntries.size(); ++i) {
        if (!m_touristEntries[i].m_isRemoved) {
            if (visibleCount == view_idx) {
                return static_cast<size_t>(i);
            }
            ++visibleCount;
        }
    }
    throw std::out_of_range("Variable view_idx out of range");
}

size_t DataStorage::touristPackageEntryViewIndexToRealIndex(const size_t view_idx) {
    assert(m_touristPackageEntries.size() > view_idx);
    size_t visibleCount = 0;
    for (int i = 0; i < m_touristPackageEntries.size(); ++i) {
        if (!m_touristPackageEntries[i].m_isRemoved) {
            if (visibleCount == view_idx) {
                return static_cast<size_t>(i);
            }
            ++visibleCount;
        }
    }
    throw std::out_of_range("Variable view_idx out of range");
}

size_t DataStorage::getDestinationEntriesViewCount() {
    size_t count = 0;
    for (auto const &entry : m_destinationEntries) {
        if (!entry.m_isRemoved) {
            ++count;
        }
    }
    return count;
}

size_t DataStorage::getTouristEntriesViewCount() {
    size_t count = 0;
    for (auto const &entry : m_touristEntries) {
        if (!entry.m_isRemoved) {
            ++count;
        }
    }
    return count;
}

size_t DataStorage::getTouristPackageEntriesViewCount() {
    size_t count = 0;
    for (auto const &entry : m_touristPackageEntries) {
        if (!entry.m_isRemoved) {
            ++count;
        }
    }
    return count;
}

bool DataStorage::saveToFile(const QString &filename) const {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_0); // Qt 5 версия

    out << m_destinationEntries;
    out << m_touristEntries;
    out << m_touristPackageEntries;

    return true;
}

bool DataStorage::loadFromFile(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_0);

    m_destinationEntries.clear();
    m_touristEntries.clear();
    m_touristPackageEntries.clear();

    in >> m_destinationEntries;
    in >> m_touristEntries;
    in >> m_touristPackageEntries;

    return in.status() == QDataStream::Ok;
}

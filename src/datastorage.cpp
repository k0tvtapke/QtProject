#include "datastorage.h"
#include <QDataStream>
#include <cassert>
#include <stdexcept>

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

namespace {
    template<typename T>
    size_t viewCountOf(const QList<T> &list) {
        size_t count = 0;
        for (const auto &entry : list) {
            if (!entry.m_isRemoved) {
                ++count;
            }
        }
        return count;
    }

    template<typename T>
    size_t viewIndexToRealIndexOf(const QList<T> &list, size_t view_idx) {
        size_t visibleCount = 0;
        for (int i = 0; i < list.size(); ++i) {
            if (!list[i].m_isRemoved) {
                if (visibleCount == view_idx) {
                    return static_cast<size_t>(i);
                }
                ++visibleCount;
            }
        }
        throw std::out_of_range("Variable view_idx out of range");
    }

    template<typename T>
    void addEntryTo(QList<T> &list, T new_entry) {
        new_entry.m_id = static_cast<quint32>(list.size());
        list.append(new_entry);
    }

    template<typename T>
    void deleteEntryFrom(QList<T> &list, size_t idx) {
        assert(static_cast<size_t>(list.size()) > idx);
        assert(!list[idx].m_isRemoved);
        list[idx].m_isRemoved = true;
    }
}

void DataStorage::addDestinationEntry(DestinationEntry new_entry) {
    addEntryTo(m_destinationEntries, new_entry);
}

void DataStorage::addTouristEntry(TouristEntry new_entry) {
    addEntryTo(m_touristEntries, new_entry);
}

void DataStorage::addTouristPackageEntry(TouristPackageEntry new_entry) {
    addEntryTo(m_touristPackageEntries, new_entry);
}

void DataStorage::deleteDestinationEntry(const size_t idx) {
    deleteEntryFrom(m_destinationEntries, idx);
}

void DataStorage::deleteTouristEntry(const size_t idx) {
    deleteEntryFrom(m_touristEntries, idx);
}

void DataStorage::deleteTouristPackageEntry(const size_t idx) {
    deleteEntryFrom(m_touristPackageEntries, idx);
}

size_t DataStorage::destinationEntryViewIndexToRealIndex(const size_t view_idx) {
    return viewIndexToRealIndexOf(m_destinationEntries, view_idx);
}

size_t DataStorage::touristEntryViewIndexToRealIndex(const size_t view_idx) {
    return viewIndexToRealIndexOf(m_touristEntries, view_idx);
}

size_t DataStorage::touristPackageEntryViewIndexToRealIndex(const size_t view_idx) {
    return viewIndexToRealIndexOf(m_touristPackageEntries, view_idx);
}

size_t DataStorage::getDestinationEntriesViewCount() {
    return viewCountOf(m_destinationEntries);
}

size_t DataStorage::getTouristEntriesViewCount() {
    return viewCountOf(m_touristEntries);
}

size_t DataStorage::getTouristPackageEntriesViewCount() {
    return viewCountOf(m_touristPackageEntries);
}

bool DataStorage::saveToFile(const QString &filename) const {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_0);

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

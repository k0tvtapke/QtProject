#include "datastorage.h"

DestinationEntry::DestinationEntry(QString country,
                                   QString city,
                                   qreal basePrice,
                                   FoodType foodType,
                                   quint8 hotelStars) : m_country(country),
                                                        m_city(city),
                                                        m_basePrice(basePrice),
                                                        m_foodType(foodType),
                                                        m_hotelStars(hotelStars) {
};

TouristEntry::TouristEntry(QString firstName,
                           QString lastName,
                           Gender gender,
                           QDate birthDate) : m_firstName(firstName),
                                              m_lastName(lastName),
                                              m_gender(gender),
                                              m_birthDate(birthDate) {
};

TouristEntry::TouristEntry(QString firstName,
                           QString lastName,
                           QString surname,
                           Gender gender,
                           QDate birthDate) : m_firstName(firstName),
                                              m_lastName(lastName),
                                              m_surname(surname),
                                              m_gender(gender),
                                              m_birthDate(birthDate) {
};

TouristPackageEntry::TouristPackageEntry(QList<quint32> touristsIds,
                                         quint32 destinationId,
                                         QDate arrivalDate,
                                         quint32 duration,
                                         qreal finalPrice) : m_touristsIds(touristsIds),
                                                             m_destinationId(destinationId),
                                                             m_arrivalDate(arrivalDate),
                                                             m_duration(duration),
                                                             m_finalPrice(finalPrice) {
};

inline QDataStream &operator<<(QDataStream &out, const Gender &g) {
    return out << static_cast<int>(g);
}

inline QDataStream &operator>>(QDataStream &in, Gender &g) {
    int v;
    in >> v;
    g = static_cast<Gender>(v);
    return in;
}

inline QDataStream &operator<<(QDataStream &out, const FoodType &f) {
    return out << static_cast<int>(f);
}

inline QDataStream &operator>>(QDataStream &in, FoodType &f) {
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

inline QDataStream &operator<<(QDataStream &out, const DestinationEntry &d) {
    out << d.m_id
            << d.m_country
            << d.m_city
            << d.m_basePrice
            << d.m_foodType
            << d.m_hotelStars
            << d.m_isRemoved;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, DestinationEntry &d) {
    in >> d.m_id
            >> d.m_country
            >> d.m_city
            >> d.m_basePrice
            >> d.m_foodType
            >> d.m_hotelStars
            >> d.m_isRemoved;
    return in;
}

inline QDataStream &operator<<(QDataStream &out, const TouristEntry &t) {
    out << t.m_id
            << t.m_firstName
            << t.m_lastName
            << t.m_surname
            << t.m_gender
            << t.m_birthDate
            << t.m_isRemoved;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, TouristEntry &t) {
    in >> t.m_id
            >> t.m_firstName
            >> t.m_lastName
            >> t.m_surname
            >> t.m_gender
            >> t.m_birthDate
            >> t.m_isRemoved;
    return in;
}

inline QDataStream &operator<<(QDataStream &out, const TouristPackageEntry &p) {
    out << p.m_id
            << p.m_touristsIds
            << p.m_destinationId
            << p.m_arrivalDate
            << p.m_duration
            << p.m_finalPrice
            << p.m_isRemoved;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, TouristPackageEntry &p) {
    in >> p.m_id
            >> p.m_touristsIds
            >> p.m_destinationId
            >> p.m_arrivalDate
            >> p.m_duration
            >> p.m_finalPrice
            >> p.m_isRemoved;
    return in;
}

void DataStorage::addDestinationEntry(DestinationEntry new_entry) {
    new_entry.m_id = m_destinationEntries.size();
    m_destinationEntries.append(new_entry);
}

void DataStorage::addTouristEntry(TouristEntry new_entry) {
    new_entry.m_id = m_touristEntries.size();
    m_touristEntries.append(new_entry);
}

void DataStorage::addTouristPackageEntry(TouristPackageEntry new_entry) {
    new_entry.m_id = m_touristPackageEntries.size();
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

bool DataStorage::saveToFile(const QString &filename) const {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_0);

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
    in.setVersion(QDataStream::Qt_6_0);

    m_destinationEntries.clear();
    m_touristEntries.clear();
    m_touristPackageEntries.clear();

    in >> m_destinationEntries;
    in >> m_touristEntries;
    in >> m_touristPackageEntries;

    if (in.status() != QDataStream::Ok) {
        return false;
    }

    return true;
}

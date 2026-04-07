#include "models/touristtablemodel.h"

TouristTableModel::TouristTableModel(DataStorage *dataStorage, QObject *parent) : m_dataStorage(dataStorage),
    QAbstractTableModel(parent) {
}

int TouristTableModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_dataStorage->m_touristEntries.size();
}

int TouristTableModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return kTouristEntryColumnCount;
}

QVariant TouristTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();

    if (index.row() >= m_dataStorage->m_touristEntries.size()) return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
            case 0:
                return m_dataStorage->m_touristEntries[index.row()].m_id.value();
            case 1:
                return m_dataStorage->m_touristEntries[index.row()].m_firstName;
            case 2:
                return m_dataStorage->m_touristEntries[index.row()].m_lastName;
            case 3:
                return m_dataStorage->m_touristEntries[index.row()].m_surname;
            case 4:
                return kGenders[static_cast<size_t>(m_dataStorage->m_touristEntries[index.row()].m_gender)];
            case 5:
                return m_dataStorage->m_touristEntries[index.row()].m_birthDate;
        }
    }

    return QVariant();
}

QVariant TouristTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case 0: return "ID";
            case 1: return "Имя";
            case 2: return "Фамилия";
            case 3: return "Отчество";
            case 4: return "Пол";
            case 5: return "Дата рождения";
        }
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

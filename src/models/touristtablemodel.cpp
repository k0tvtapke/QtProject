#include "models/touristtablemodel.h"

TouristTableModel::TouristTableModel(DataStorage *dataStorage, QObject *parent) : BaseTableModel(dataStorage, parent) {
}

int TouristTableModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_dataStorage->getTouristEntriesViewCount();
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

    auto entry = m_dataStorage->m_touristEntries[m_dataStorage->touristEntryViewIndexToRealIndex(index.row())];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
            case 0:
                return entry.m_id.value();
            case 1:
                return entry.m_firstName;
            case 2:
                return entry.m_lastName;
            case 3:
                return entry.m_surname;
            case 4:
                return kGenders[static_cast<size_t>(entry.m_gender)];
            case 5:
                return entry.m_birthDate;
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

void TouristTableModel::removeEntry(size_t view_idx, const QModelIndex &parent) {
    size_t real_idx = m_dataStorage->touristEntryViewIndexToRealIndex(view_idx);

    beginRemoveRows(parent, view_idx, view_idx);
    m_dataStorage->deleteTouristEntry(real_idx);
    endRemoveRows();
}

size_t TouristTableModel::viewIndexToRealIndex(size_t view_idx) {
    return m_dataStorage->touristEntryViewIndexToRealIndex(view_idx);
}

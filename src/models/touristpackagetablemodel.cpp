#include "models/touristpackagemodel.h"

TouristPackageTableModel::TouristPackageTableModel(DataStorage *dataStorage, QObject *parent) : BaseTableModel(
    dataStorage, parent) {
}

int TouristPackageTableModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_dataStorage->getTouristPackageEntriesViewCount();
}

int TouristPackageTableModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return kTouristPackageEntryColumnCount;
}

QVariant TouristPackageTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();

    if (index.row() >= m_dataStorage->m_touristPackageEntries.size()) return QVariant();

    auto entry = m_dataStorage->m_touristPackageEntries[m_dataStorage->
        touristPackageEntryViewIndexToRealIndex(index.row())];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
            case 0:
                return entry.m_id.value();
            case 1: {
                QString result = "";
                bool isFirstElement = true;

                for (auto id: entry.m_touristsIds) {
                    if (isFirstElement) {
                        isFirstElement = false;
                    } else {
                        result += ", ";
                    }
                    result += m_dataStorage->m_touristEntries[id].m_lastName + " " +
                            m_dataStorage->m_touristEntries[id].m_firstName +
                            (m_dataStorage->m_touristEntries[id].m_surname.isEmpty()
                                 ? ""
                                 : (" " +
                                    m_dataStorage->m_touristEntries[id].m_surname)) + " (ID: " + QString::number(id) +
                            ")";
                }

                return result;
            }
            case 2: {
                auto id = entry.m_destinationId;

                return m_dataStorage->m_destinationEntries[id].m_country + ", " + m_dataStorage->m_destinationEntries[
                           id]
                       .m_city + " (ID: " + QString::number(id) + ")";
            }
            case 3:
                return entry.m_arrivalDate;
            case 4:
                return entry.m_duration;
            case 5:
                return entry.m_finalPrice;
        }
    }

    return QVariant();
}

QVariant TouristPackageTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case 0: return "ID";
            case 1: return "Туристы";
            case 2: return "Направление";
            case 3: return "Дата отправки";
            case 4: return "Длительность";
            case 5: return "Итоговая цена";
        }
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

void TouristPackageTableModel::removeEntry(size_t view_idx, const QModelIndex &parent) {
    size_t real_idx = m_dataStorage->touristPackageEntryViewIndexToRealIndex(view_idx);

    beginRemoveRows(parent, view_idx, view_idx);
    m_dataStorage->deleteTouristPackageEntry(real_idx);
    endRemoveRows();
}

size_t TouristPackageTableModel::viewIndexToRealIndex(size_t view_idx) {
    return m_dataStorage->touristPackageEntryViewIndexToRealIndex(view_idx);
}

#include "models/destinationtablemodel.h"

DestinationTableModel::DestinationTableModel(DataStorage *dataStorage, QObject *parent) : BaseTableModel(
    dataStorage, parent) {
}

int DestinationTableModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_dataStorage->getDestinationEntriesViewCount();
}

int DestinationTableModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return kDestinationEntryColumnCount;
}

QVariant DestinationTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();

    if (index.row() >= m_dataStorage->m_destinationEntries.size()) return QVariant();

    auto entry = m_dataStorage->m_destinationEntries[m_dataStorage->destinationEntryViewIndexToRealIndex(index.row())];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
            case 0:
                return entry.m_id.value();
            case 1:
                return entry.m_country;
            case 2:
                return entry.m_city;
            case 3:
                return entry.m_basePrice;
            case 4:
                if (role == Qt::DisplayRole)
                {
                    return kFoodTypes[static_cast<size_t>(entry.m_foodType)];
                }
                return static_cast<quint32>(entry.m_foodType);
            case 5:
                return entry.m_hotelStars;
        }
    }

    return QVariant();
}

QVariant DestinationTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case 0: return "ID";
            case 1: return "Страна";
            case 2: return "Город";
            case 3: return "Базовая цена";
            case 4: return "Тип питания";
            case 5: return "Кол-во звезд отеля";
        }
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

void DestinationTableModel::removeEntry(size_t view_idx, const QModelIndex &parent) {
    size_t real_idx = m_dataStorage->destinationEntryViewIndexToRealIndex(view_idx);

    beginRemoveRows(parent, view_idx, view_idx);
    m_dataStorage->deleteDestinationEntry(real_idx);
    endRemoveRows();
}

size_t DestinationTableModel::viewIndexToRealIndex(size_t view_idx) {
    return m_dataStorage->destinationEntryViewIndexToRealIndex(view_idx);
}

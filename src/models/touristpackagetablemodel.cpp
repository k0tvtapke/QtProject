#include "models/touristpackagemodel.h"

TouristPackageTableModel::TouristPackageTableModel(DataStorage *dataStorage, QObject *parent) : BaseTableModel(
    dataStorage, parent) {
}

int TouristPackageTableModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_dataStorage->m_touristPackageEntries.size();
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

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
            case 0:
                return m_dataStorage->m_touristPackageEntries[index.row()].m_id.value();
            case 1: {
                QString result = "";
                bool isFirstElement = true;

                for (auto id: m_dataStorage->m_touristPackageEntries[index.row()].m_touristsIds) {
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
                auto id = m_dataStorage->m_touristPackageEntries[index.row()].m_destinationId;

                return m_dataStorage->m_destinationEntries[id].m_country + ", " + m_dataStorage->m_destinationEntries[
                           id]
                       .m_city + " (ID: " + QString::number(id) + ")";
            }
            case 3:
                return m_dataStorage->m_touristPackageEntries[index.row()].m_arrivalDate;
            case 4:
                return m_dataStorage->m_touristPackageEntries[index.row()].m_duration;
            case 5:
                return m_dataStorage->m_touristPackageEntries[index.row()].m_finalPrice;
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

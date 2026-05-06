#ifndef TOURISTPACKAGETABLEMODEL_H
#define TOURISTPACKAGETABLEMODEL_H

#include "datastorage.h"
#include "models/basetablemodel.h"

#include <QVariant>

/**
 * @brief Кол-во столбцов в таблице путёвок: ID, туристы, направление, дата, длительность, цена.
 */
constexpr int kTouristPackageEntryColumnCount = 6;

/**
 * @class TouristPackageTableModel
 * @brief Табличная модель для путёвок (`TouristPackageEntry`).
 * @extends BaseTableModel
 */
class TouristPackageTableModel : public BaseTableModel {
    Q_OBJECT

public:
    TouristPackageTableModel(DataStorage *dataStorage, QObject *parent);

    /**
     * @override QAbstractTableModel::rowCount
     */
    int rowCount(const QModelIndex &parent) const override;

    /**
     * @override QAbstractTableModel::columnCount
     */
    int columnCount(const QModelIndex &parent) const override;

    /**
     * @override QAbstractTableModel::data
     * @details Для столбцов «туристы» и «направление» при `Qt::EditRole`
     *          возвращает значения, удобные для сортировки/фильтрации.
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * @override QAbstractTableModel::headerData
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    /**
     * @override BaseTableModel::removeEntry
     */
    void removeEntry(size_t view_idx, const QModelIndex &parent) override;

    /**
     * @override BaseTableModel::viewIndexToRealIndex
     */
    size_t viewIndexToRealIndex(size_t view_idx) override;
};

#endif // TOURISTPACKAGETABLEMODEL_H

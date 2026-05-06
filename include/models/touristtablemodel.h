#ifndef TOURISTTABLEMODEL_H
#define TOURISTTABLEMODEL_H

#include "datastorage.h"
#include "models/basetablemodel.h"
#include "util/enumlabels.h"

#include <QVariant>

/**
 * @brief Кол-во столбцов в таблице туристов: ID, имя, фамилия, отчество, пол, ДР.
 */
constexpr int kTouristEntryColumnCount = 6;

/**
 * @class TouristTableModel
 * @brief Табличная модель для туристов (`TouristEntry`).
 * @extends BaseTableModel
 */
class TouristTableModel : public BaseTableModel {
    Q_OBJECT

public:
    TouristTableModel(DataStorage *dataStorage, QObject *parent);

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
     * @details Для столбца «дата рождения» при `Qt::EditRole` возвращает QDate
     *          (для корректной сортировки), при `Qt::DisplayRole` — отформатированную строку.
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

#endif // TOURISTTABLEMODEL_H

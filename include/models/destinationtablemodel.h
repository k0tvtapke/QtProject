#ifndef DESTINATIONTABLEMODEL_H
#define DESTINATIONTABLEMODEL_H

#include "datastorage.h"
#include "models/basetablemodel.h"
#include "util/enumlabels.h"

#include <QVariant>

/**
 * @brief Кол-во столбцов в таблице направлений: ID, страна, город, цена, питание, звёзды.
 */
constexpr int kDestinationEntryColumnCount = 6;

/**
 * @class DestinationTableModel
 * @brief Табличная модель для направлений (`DestinationEntry`).
 * @extends BaseTableModel
 */
class DestinationTableModel : public BaseTableModel {
    Q_OBJECT

public:
    /**
     * @brief Конструктор.
     */
    DestinationTableModel(DataStorage *dataStorage, QObject *parent);

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
     * @details Для столбца «питание» при `Qt::EditRole` возвращает числовой код
     *          (для сортировки), при `Qt::DisplayRole` — человекочитаемую строку.
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

#endif // DESTINATIONTABLEMODEL_H

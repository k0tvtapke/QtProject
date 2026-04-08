#ifndef TOURISTPACKAGETABLEMODEL_H
#define TOURISTPACKAGETABLEMODEL_H

#include "datastorage.h"
#include "models/basetablemodel.h"

#include <QVariant>

constexpr int kTouristPackageEntryColumnCount = 6;

class TouristPackageTableModel : public BaseTableModel {
    Q_OBJECT

public:
    TouristPackageTableModel(DataStorage *dataStorage, QObject *parent);

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void removeEntry(size_t view_idx, const QModelIndex &parent) override;

    size_t viewIndexToRealIndex(size_t view_idx) override;
};

#endif // TOURISTPACKAGETABLEMODEL_H

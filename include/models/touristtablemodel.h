#ifndef TOURISTTABLEMODEL_H
#define TOURISTTABLEMODEL_H

#include "../datastorage.h"

#include <QAbstractTableModel>
#include <QVariant>

const QString kGenders[]{
    "Мужской",
    "Женский"
};

class TouristTableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    TouristTableModel(DataStorage *dataStorage, QObject *parent);

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    DataStorage *m_dataStorage;
};

#endif // TOURISTTABLEMODEL_H

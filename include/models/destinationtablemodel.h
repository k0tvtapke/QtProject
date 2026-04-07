#ifndef DESTINATIONTABLEMODEL_H
#define DESTINATIONTABLEMODEL_H

#include "datastorage.h"

#include <QAbstractTableModel>
#include <QVariant>

const QString kFoodTypes[]{
    "Без питания",
    "Только завтрак",
    "Полупансион",
    "Полный пансион",
    "Все включено",
    "Ультра все включено"
};

class DestinationTableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    DestinationTableModel(DataStorage *dataStorage, QObject *parent);

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

public slots:
    void reloadTable();

private:
    DataStorage *m_dataStorage;
};

#endif // DESTINATIONTABLEMODEL_H

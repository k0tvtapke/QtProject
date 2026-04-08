#ifndef BASETABLEMODEL_H
#define BASETABLEMODEL_H

#include "datastorage.h"

#include <QAbstractTableModel>

class BaseTableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    BaseTableModel(DataStorage *dataStorage, QObject *parent);

    virtual void removeEntry(size_t view_idx, const QModelIndex &parent) = 0;

public slots:
    void reloadTable();

protected:
    DataStorage *m_dataStorage;
};

#endif //BASETABLEMODEL_H

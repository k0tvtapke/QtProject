#include "models/basetablemodel.h"

BaseTableModel::BaseTableModel(DataStorage *dataStorage, QObject *parent) : QAbstractTableModel(parent),
                                                                            m_dataStorage(dataStorage) {
}

void BaseTableModel::reloadTable() {
    beginResetModel();
    endResetModel();
}

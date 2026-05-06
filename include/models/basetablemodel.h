#ifndef BASETABLEMODEL_H
#define BASETABLEMODEL_H

#include "datastorage.h"

#include <QAbstractTableModel>

/**
 * @class BaseTableModel
 * @brief Общий контракт табличной модели поверх `DataStorage`.
 * @details Скрывает удалённые записи, конвертирует view-индексы в реальные
 *          и предоставляет операции удаления/перезагрузки.
 *
 * @extends QAbstractTableModel
 */
class BaseTableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    /**
     * @brief Конструктор.
     * @param dataStorage Указатель на in-memory БД (без владения).
     * @param parent Родитель в дереве QObject.
     */
    BaseTableModel(DataStorage *dataStorage, QObject *parent);

    /**
     * @brief Удалить запись по view-индексу.
     * @pure
     */
    virtual void removeEntry(size_t view_idx, const QModelIndex &parent) = 0;

    /**
     * @brief Перевести view-индекс в реальный индекс хранилища.
     * @pure
     */
    virtual size_t viewIndexToRealIndex(size_t view_idx) = 0;

public slots:
    /**
     * @brief Триггер beginResetModel/endResetModel — полная перерисовка таблицы.
     */
    void reloadTable();

protected:
    DataStorage *m_dataStorage;     ///< Хранилище данных (без владения).
};

#endif //BASETABLEMODEL_H

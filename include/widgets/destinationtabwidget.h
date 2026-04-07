#ifndef DESTINATIONTABWIDGET_H
#define DESTINATIONTABWIDGET_H

#include "widgets/databasetabwidget.h"
#include "../datastorage.h"
#include "models/destinationtablemodel.h"

class DestinationTabWidget : public DatabaseTabWidget
{
    Q_OBJECT
public:
    explicit DestinationTabWidget(DataStorage *storage, QWidget *parent = nullptr);
    ~DestinationTabWidget() override;

private:
    DataStorage *m_dataStorage;

    DestinationTableModel *m_tableModel;

    void onAddEntryButtonClicked() override;
    void onDeleteEntryButtonClicked() override;
    void onCreateReportButtonClicked() override;
};

#endif // DESTINATIONTABWIDGET_H

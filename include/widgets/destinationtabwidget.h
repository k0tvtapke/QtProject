#ifndef DESTINATIONTABWIDGET_H
#define DESTINATIONTABWIDGET_H

#include "datastorage.h"
#include "widgets/databasetabwidget.h"

class DestinationTabWidget : public DatabaseTabWidget
{
    Q_OBJECT
public:
    explicit DestinationTabWidget(DataStorage *storage, QWidget *parent = nullptr);
    ~DestinationTabWidget() override;

private:
    DataStorage *m_dataStorage;

    void onAddEntryButtonClicked() override;
    void onDeleteEntryButtonClicked() override;
    void onCreateReportButtonClicked() override;
};

#endif // DESTINATIONTABWIDGET_H

#ifndef DESTINATIONTABWIDGET_H
#define DESTINATIONTABWIDGET_H

#include "datastorage.h"
#include "widgets/databasetabwidget.h"

class DestinationTabWidget : public DatabaseTabWidget {
    Q_OBJECT

public:
    explicit DestinationTabWidget(DataStorage *storage, QWidget *parent = nullptr);

private:
    DataStorage *m_dataStorage;

    void on_addEntryButton_clicked() override;

    void on_deleteEntryButton_clicked() override;

    void on_createReportButton_clicked() override;
};

#endif // DESTINATIONTABWIDGET_H

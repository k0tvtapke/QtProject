#ifndef TOURISTTABWIDGET_H
#define TOURISTTABWIDGET_H

#include "datastorage.h"
#include "widgets/databasetabwidget.h"

class TouristTabWidget : public DatabaseTabWidget {
    Q_OBJECT

public:
    explicit TouristTabWidget(DataStorage *storage, QWidget *parent = nullptr);

private:
    DataStorage *m_dataStorage;

    void on_addEntryButton_clicked() override;

    void on_deleteEntryButton_clicked() override;

    void on_createReportButton_clicked() override;
};

#endif // TOURISTTABWIDGET_H

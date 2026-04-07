#ifndef TOURISTTABWIDGET_H
#define TOURISTTABWIDGET_H

#include "widgets/databasetabwidget.h"
#include "datastorage.h"

class TouristTabWidget : public DatabaseTabWidget
{
    Q_OBJECT
public:
    explicit TouristTabWidget(DataStorage *storage, QWidget *parent = nullptr);
    ~TouristTabWidget() override;

private:
    DataStorage *m_dataStorage;

    void onAddEntryButtonClicked() override;
    void onDeleteEntryButtonClicked() override;
    void onCreateReportButtonClicked() override;
};

#endif // TOURISTTABWIDGET_H

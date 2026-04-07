#ifndef TOURISTPACKAGETABWIDGET_H
#define TOURISTPACKAGETABWIDGET_H

#include "widgets/databasetabwidget.h"
#include "../datastorage.h"
#include "models/touristpackagemodel.h"

class TouristPackageTabWidget : public DatabaseTabWidget
{
    Q_OBJECT
public:
    explicit TouristPackageTabWidget(DataStorage *storage, QWidget *parent = nullptr);
    ~TouristPackageTabWidget() override;

private:
    DataStorage *m_dataStorage;

    TouristPackageTableModel *m_tableModel;

    void onAddEntryButtonClicked() override;
    void onDeleteEntryButtonClicked() override;
    void onCreateReportButtonClicked() override;
};

#endif // TOURISTPACKAGETABWIDGET_H

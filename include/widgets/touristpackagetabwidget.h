#ifndef TOURISTPACKAGETABWIDGET_H
#define TOURISTPACKAGETABWIDGET_H

#include "datastorage.h"
#include "widgets/databasetabwidget.h"

class TouristPackageTabWidget : public DatabaseTabWidget {
    Q_OBJECT

public:
    explicit TouristPackageTabWidget(DataStorage *storage, QWidget *parent = nullptr);

private:
    DataStorage *m_dataStorage;

    void on_addEntryButton_clicked() override;

    void on_deleteEntryButton_clicked() override;

    void on_createReportButton_clicked() override;
};

#endif // TOURISTPACKAGETABWIDGET_H

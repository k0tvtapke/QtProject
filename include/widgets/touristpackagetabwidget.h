#ifndef TOURISTPACKAGETABWIDGET_H
#define TOURISTPACKAGETABWIDGET_H

#include "datastorage.h"
#include "widgets/basetabwidget.h"

class TouristPackageTabWidget : public BaseTabWidget {
    Q_OBJECT

public:
    explicit TouristPackageTabWidget(DataStorage *storage, QWidget *parent = nullptr);

private:
    DataStorage *m_dataStorage;

    void on_addEntryButton_clicked() override;

    void on_editEntryButton_clicked() override;

    void on_deleteEntryButton_clicked() override;

    void on_createReportButton_clicked() override;
};

#endif // TOURISTPACKAGETABWIDGET_H

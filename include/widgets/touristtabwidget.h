#ifndef TOURISTTABWIDGET_H
#define TOURISTTABWIDGET_H

#include "datastorage.h"
#include "widgets/basetabwidget.h"

class TouristTabWidget : public BaseTabWidget
{
    Q_OBJECT

public:
    explicit TouristTabWidget(DataStorage* storage, QWidget* parent = nullptr);

private:
    DataStorage* m_dataStorage;

    void on_addEntryButton_clicked() override;

    void on_editEntryButton_clicked() override;

    void on_deleteEntryButton_clicked() override;

    void on_createReportButton_clicked() override;

private slots:
    void onShowChartButtonClicked();
};

#endif // TOURISTTABWIDGET_H

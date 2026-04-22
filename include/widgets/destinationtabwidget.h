#ifndef DESTINATIONTABWIDGET_H
#define DESTINATIONTABWIDGET_H

#include "datastorage.h"
#include "widgets/basetabwidget.h"

class DestinationTabWidget : public BaseTabWidget {
    Q_OBJECT

public:
    explicit DestinationTabWidget(DataStorage *storage, QWidget *parent = nullptr);

protected:
    DataStorage *m_dataStorage;

    void on_addEntryButton_clicked() override;

    void on_editEntryButton_clicked() override;

    void on_deleteEntryButton_clicked() override;

    void on_createReportButton_clicked() override;
};

#endif // DESTINATIONTABWIDGET_H

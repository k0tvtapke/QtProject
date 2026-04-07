#ifndef DATABASETABWIDGET_H
#define DATABASETABWIDGET_H

#include "models/destinationtablemodel.h"

#include <QWidget>
#include <QSortFilterProxyModel>

namespace Ui {
class DatabaseTabWidget;
}

class DatabaseTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseTabWidget(QWidget *parent = nullptr);
    ~DatabaseTabWidget() override;

protected:
    Ui::DatabaseTabWidget *ui;

    virtual void onAddEntryButtonClicked() = 0;
    virtual void onDeleteEntryButtonClicked() = 0;
    virtual void onCreateReportButtonClicked() = 0;
private slots:
    void on_addEntryButton_clicked();
    void on_deleteEntryButton_clicked();
    void on_createReportButton_clicked();
};

#endif // DATABASETABWIDGET_H

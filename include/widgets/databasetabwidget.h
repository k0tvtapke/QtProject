#ifndef DATABASETABWIDGET_H
#define DATABASETABWIDGET_H

#include "models/basetablemodel.h"

#include <QWidget>

namespace Ui {
class DatabaseTabWidget;
}

class DatabaseTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseTabWidget(BaseTableModel *tableModel, QWidget *parent = nullptr);
    ~DatabaseTabWidget() override;

    void reloadTable();

protected:
    Ui::DatabaseTabWidget *ui;

    BaseTableModel *m_tableModel;

    virtual void onAddEntryButtonClicked() = 0;
    virtual void onDeleteEntryButtonClicked() = 0;
    virtual void onCreateReportButtonClicked() = 0;
private slots:
    void on_addEntryButton_clicked();
    void on_deleteEntryButton_clicked();
    void on_createReportButton_clicked();
};

#endif // DATABASETABWIDGET_H

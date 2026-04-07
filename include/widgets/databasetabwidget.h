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

protected slots:
    virtual void on_addEntryButton_clicked() = 0;
    virtual void on_deleteEntryButton_clicked() = 0;
    virtual void on_createReportButton_clicked() = 0;
};

#endif // DATABASETABWIDGET_H

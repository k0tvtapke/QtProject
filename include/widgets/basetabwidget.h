#ifndef BASETABWIDGET_H
#define BASETABWIDGET_H

#include "models/basetablemodel.h"

#include <QWidget>
#include <QItemSelection>

namespace Ui {
class BaseTabWidget;
}

class BaseTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BaseTabWidget(BaseTableModel *tableModel, QWidget *parent = nullptr);
    ~BaseTabWidget() override;

    void reloadTable();
    void resizeTable();

protected:
    Ui::BaseTabWidget *ui;

    BaseTableModel *m_tableModel;

protected slots:
    virtual void on_addEntryButton_clicked() = 0;
    virtual void on_editEntryButton_clicked() = 0;
    virtual void on_deleteEntryButton_clicked() = 0;
    virtual void on_createReportButton_clicked() = 0;

private slots:
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
};

#endif // BASETABWIDGET_H

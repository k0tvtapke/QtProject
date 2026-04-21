#ifndef BASETABWIDGET_H
#define BASETABWIDGET_H

#include "models/basetablemodel.h"

#include <QWidget>
#include <QItemSelection>
#include <QSortFilterProxyModel>

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
    QSortFilterProxyModel *m_sortFilterModel;

protected slots:
    virtual void on_addEntryButton_clicked() = 0;
    virtual void on_editEntryButton_clicked() = 0;
    virtual void on_deleteEntryButton_clicked() = 0;
    virtual void on_createReportButton_clicked() = 0;

private slots:
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void on_searchFilterComboBox_currentIndexChanged(int index);
    void on_searchFilterLineEdit_textChanged(const QString &text);
    void on_resetFilterPushButton_clicked();
};

#endif // BASETABWIDGET_H

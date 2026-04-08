#ifndef ENTRYSELECTIONDIALOG_H
#define ENTRYSELECTIONDIALOG_H

#include "models/basetablemodel.h"

#include <QDialog>
#include <QItemSelection>

namespace Ui {
    class EntrySelectionDialog;
}

class EntrySelectionDialog : public QDialog {
    Q_OBJECT

public:
    explicit EntrySelectionDialog(bool isSingleSelection, BaseTableModel *tableModel, QWidget *parent = nullptr);

    ~EntrySelectionDialog();

    QList<quint32> getChosenIndexes();

    quint32 getChosenIndex();

private:
    Ui::EntrySelectionDialog *ui;

    bool m_isSingleSelection;
    BaseTableModel *m_tableModel;

private slots:
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    void on_addDestinationSelectionButton_clicked();

    void on_cancelDestinationSelectionButton_clicked();
};

#endif // ENTRYSELECTIONDIALOG_H

#include "widgets/touristtabwidget.h"
#include "ui_databasetabwidget.h"

#include "models/touristtablemodel.h"
#include "dialogs/newtouristentrydialog.h"

#include <QMessageBox>

TouristTabWidget::TouristTabWidget(DataStorage *storage, QWidget *parent) : m_dataStorage(storage),
                                                                            DatabaseTabWidget(
                                                                                new TouristTableModel(storage, parent),
                                                                                parent) {
    ui->databaseTable->setSortingEnabled(true);
    ui->databaseTable->resizeColumnsToContents();
    ui->databaseTable->setWordWrap(true);
    ui->databaseTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void TouristTabWidget::on_addEntryButton_clicked() {
    NewTouristEntryDialog dialog(m_dataStorage->m_touristEntries.size(), this);

    if (dialog.exec()) {
        m_dataStorage->addTouristEntry(dialog.getTouristEntry());
        reloadTable();
    }
}

void TouristTabWidget::on_deleteEntryButton_clicked() {
    QModelIndexList selectedIndexes = ui->databaseTable->selectionModel()->selectedRows();

    QModelIndex index = selectedIndexes.first();

    if (QMessageBox::question(this, "Подтверждение удаления",
                              QString("Вы действительно хотите удалить запись?"))
        != QMessageBox::Yes) {
        return;
        }

    if (!index.isValid()) return;

    m_tableModel->removeEntry(index.row(), QModelIndex());
}

void TouristTabWidget::on_createReportButton_clicked() {
}

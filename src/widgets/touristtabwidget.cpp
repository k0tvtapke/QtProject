#include "widgets/touristtabwidget.h"
#include "ui_basetabwidget.h"

#include "models/touristtablemodel.h"
#include "dialogs/newtouristentrydialog.h"

#include <QMessageBox>

TouristTabWidget::TouristTabWidget(DataStorage *storage, QWidget *parent) : m_dataStorage(storage),
                                                                            BaseTabWidget(
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

    resizeTable();
}

void TouristTabWidget::on_editEntryButton_clicked() {
    QModelIndexList selectedIndexes = ui->databaseTable->selectionModel()->selectedRows();

    QModelIndex index = selectedIndexes.first();
    size_t real_idx = m_dataStorage->touristEntryViewIndexToRealIndex(index.row());

    NewTouristEntryDialog dialog(
        &m_dataStorage->m_touristEntries[real_idx], this);

    if (dialog.exec()) {
        m_dataStorage->m_touristEntries[real_idx] = dialog.getTouristEntry();
        reloadTable();
        ui->editEntryButton->setDisabled(true);
        ui->deleteEntryButton->setDisabled(true);
    }

    resizeTable();
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

    resizeTable();
}

void TouristTabWidget::on_createReportButton_clicked() {
}

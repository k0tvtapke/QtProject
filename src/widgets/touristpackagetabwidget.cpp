#include "widgets/touristpackagetabwidget.h"
#include "ui_basetabwidget.h"

#include "models/touristpackagemodel.h"
#include "dialogs/newtouristpackageentrydialog.h"

#include <QMessageBox>

TouristPackageTabWidget::TouristPackageTabWidget(DataStorage *storage, QWidget *parent) : m_dataStorage(storage),
    BaseTabWidget(new TouristPackageTableModel(storage, parent), parent) {
    ui->databaseTable->setSortingEnabled(true);
    ui->databaseTable->resizeColumnsToContents();
    ui->databaseTable->setWordWrap(true);
    ui->databaseTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void TouristPackageTabWidget::on_addEntryButton_clicked() {
    NewTouristPackageEntryDialog dialog(m_dataStorage->m_touristPackageEntries.size(), m_dataStorage, this);

    if (dialog.exec()) {
        m_dataStorage->addTouristPackageEntry(dialog.getTouristPackageEntry());
        reloadTable();
    }

    resizeTable();
}

void TouristPackageTabWidget::on_editEntryButton_clicked() {
    QModelIndexList selectedIndexes = ui->databaseTable->selectionModel()->selectedRows();

    QModelIndex index = selectedIndexes.first();
    size_t real_idx = m_dataStorage->touristPackageEntryViewIndexToRealIndex(index.row());

    NewTouristPackageEntryDialog dialog(&m_dataStorage->m_touristPackageEntries[real_idx], m_dataStorage, this);

    if (dialog.exec()) {
        m_dataStorage->m_touristPackageEntries[real_idx] = dialog.getTouristPackageEntry();
        reloadTable();

        ui->editEntryButton->setDisabled(true);
        ui->deleteEntryButton->setDisabled(true);
    }

    resizeTable();
}

void TouristPackageTabWidget::on_deleteEntryButton_clicked() {
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

void TouristPackageTabWidget::on_createReportButton_clicked() {
}

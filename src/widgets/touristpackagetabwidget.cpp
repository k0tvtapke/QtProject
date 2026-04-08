#include "widgets/touristpackagetabwidget.h"
#include "ui_databasetabwidget.h"

#include "models/touristpackagemodel.h"

#include <QMessageBox>

TouristPackageTabWidget::TouristPackageTabWidget(DataStorage *storage, QWidget *parent) : m_dataStorage(storage),
    DatabaseTabWidget(new TouristPackageTableModel(storage, parent), parent) {
    ui->databaseTable->setSortingEnabled(true);
    ui->databaseTable->resizeColumnsToContents();
    ui->databaseTable->setWordWrap(true);
    ui->databaseTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void TouristPackageTabWidget::on_addEntryButton_clicked() {
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
}

void TouristPackageTabWidget::on_createReportButton_clicked() {
}

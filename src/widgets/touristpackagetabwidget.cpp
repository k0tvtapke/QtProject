#include "widgets/touristpackagetabwidget.h"
#include "ui_databasetabwidget.h"

#include "models/touristpackagemodel.h"

TouristPackageTabWidget::TouristPackageTabWidget(DataStorage *storage, QWidget *parent) : m_dataStorage(storage),
    DatabaseTabWidget(new TouristPackageTableModel(storage, parent), parent) {
    ui->databaseTable->setModel(m_tableModel);
    ui->databaseTable->setSortingEnabled(true);
    ui->databaseTable->resizeColumnsToContents();
    ui->databaseTable->setWordWrap(true);
    ui->databaseTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void TouristPackageTabWidget::on_addEntryButton_clicked() {
}

void TouristPackageTabWidget::on_deleteEntryButton_clicked() {
}

void TouristPackageTabWidget::on_createReportButton_clicked() {
}

#include "widgets/touristtabwidget.h"
#include "ui_databasetabwidget.h"

#include "models/touristtablemodel.h"

TouristTabWidget::TouristTabWidget(DataStorage *storage, QWidget *parent) : m_dataStorage(storage),
                                                                            DatabaseTabWidget(
                                                                                new TouristTableModel(storage, parent),
                                                                                parent) {
    ui->databaseTable->setModel(m_tableModel);
    ui->databaseTable->setSortingEnabled(true);
    ui->databaseTable->resizeColumnsToContents();
    ui->databaseTable->setWordWrap(true);
    ui->databaseTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void TouristTabWidget::on_addEntryButton_clicked() {
}

void TouristTabWidget::on_deleteEntryButton_clicked() {
}

void TouristTabWidget::on_createReportButton_clicked() {
}

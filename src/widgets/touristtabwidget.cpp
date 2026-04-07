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

TouristTabWidget::~TouristTabWidget() {
    delete m_tableModel;
}

void TouristTabWidget::onAddEntryButtonClicked() {
}

void TouristTabWidget::onDeleteEntryButtonClicked() {
}

void TouristTabWidget::onCreateReportButtonClicked() {
}

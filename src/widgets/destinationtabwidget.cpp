#include "widgets/destinationtabwidget.h"
#include "ui_databasetabwidget.h"

#include "models/destinationtablemodel.h"


DestinationTabWidget::DestinationTabWidget(DataStorage *storage, QWidget *parent) : m_dataStorage(storage),
    DatabaseTabWidget(new DestinationTableModel(storage, parent), parent) {
    ui->databaseTable->setModel(m_tableModel);
    ui->databaseTable->setSortingEnabled(true);
    ui->databaseTable->resizeColumnsToContents();
    ui->databaseTable->setWordWrap(true);
    ui->databaseTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

DestinationTabWidget::~DestinationTabWidget() {
    delete m_tableModel;
}

void DestinationTabWidget::onAddEntryButtonClicked() {
}

void DestinationTabWidget::onDeleteEntryButtonClicked() {
}

void DestinationTabWidget::onCreateReportButtonClicked() {
}

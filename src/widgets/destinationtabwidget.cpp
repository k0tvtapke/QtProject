#include "widgets/destinationtabwidget.h"
#include "ui_databasetabwidget.h"

#include "models/destinationtablemodel.h"
#include "dialogs/newdestinationentrydialog.h"

DestinationTabWidget::DestinationTabWidget(DataStorage *storage, QWidget *parent) : m_dataStorage(storage),
    DatabaseTabWidget(new DestinationTableModel(storage, parent), parent) {
    ui->databaseTable->setModel(m_tableModel);
    ui->databaseTable->setSortingEnabled(true);
    ui->databaseTable->resizeColumnsToContents();
    ui->databaseTable->setWordWrap(true);
    ui->databaseTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void DestinationTabWidget::on_addEntryButton_clicked() {
    NewDestinationEntryDialog dialog(m_dataStorage->m_destinationEntries.size(), this);

    if (dialog.exec()) {
        m_dataStorage->addDestinationEntry(dialog.getDestinationEntry());
        reloadTable();
    }
}

void DestinationTabWidget::on_deleteEntryButton_clicked() {
}

void DestinationTabWidget::on_createReportButton_clicked() {
}

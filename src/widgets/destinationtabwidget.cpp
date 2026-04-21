#include "widgets/destinationtabwidget.h"

#include "ui_basetabwidget.h"

#include "models/destinationtablemodel.h"
#include "dialogs/newdestinationentrydialog.h"

#include <QMessageBox>
#include <QSortFilterProxyModel>

DestinationTabWidget::DestinationTabWidget(DataStorage *storage, QWidget *parent) : m_dataStorage(storage),
    BaseTabWidget(new DestinationTableModel(storage, parent), parent) {
    ui->databaseTable->setSortingEnabled(true);
    ui->databaseTable->resizeColumnsToContents();
    ui->databaseTable->setWordWrap(true);
    ui->databaseTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->searchFilterComboBox->addItem("Все столбцы", -1);
    ui->searchFilterComboBox->addItem("ID", 0);
    ui->searchFilterComboBox->addItem("Страна", 1);
    ui->searchFilterComboBox->addItem("Город", 2);
    ui->searchFilterComboBox->addItem("Базовая цена", 3);
    ui->searchFilterComboBox->addItem("Тип питания", 4);
    ui->searchFilterComboBox->addItem("Кол-во звезд отеля", 5);
}

void DestinationTabWidget::on_addEntryButton_clicked() {
    NewDestinationEntryDialog dialog(m_dataStorage->m_destinationEntries.size(), this);

    if (dialog.exec()) {
        m_dataStorage->addDestinationEntry(dialog.getDestinationEntry());
        reloadTable();
    }

    resizeTable();
}

void DestinationTabWidget::on_editEntryButton_clicked() {
    QModelIndexList selectedIndexes = ui->databaseTable->selectionModel()->selectedRows();

    QModelIndex index = m_sortFilterModel->mapToSource(selectedIndexes.first());
    size_t real_idx = m_dataStorage->destinationEntryViewIndexToRealIndex(index.row());

    NewDestinationEntryDialog dialog(
        &m_dataStorage->m_destinationEntries[real_idx], this);

    if (dialog.exec()) {
        m_dataStorage->m_destinationEntries[real_idx] = dialog.getDestinationEntry();
        reloadTable();
        ui->editEntryButton->setDisabled(true);
        ui->deleteEntryButton->setDisabled(true);
    }

    resizeTable();
}

void DestinationTabWidget::on_deleteEntryButton_clicked() {
    QModelIndexList selectedIndexes = ui->databaseTable->selectionModel()->selectedRows();

    QModelIndex index = m_sortFilterModel->mapToSource(selectedIndexes.first());

    if (QMessageBox::question(this, "Подтверждение удаления",
                              QString("Вы действительно хотите удалить запись?"))
        != QMessageBox::Yes) {
        return;
    }

    if (!index.isValid()) return;

    m_tableModel->removeEntry(index.row(), QModelIndex());

    resizeTable();
}

void DestinationTabWidget::on_createReportButton_clicked() {
}

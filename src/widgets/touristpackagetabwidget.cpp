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

    ui->searchFilterComboBox->addItem("Все столбцы", -1);
    ui->searchFilterComboBox->addItem("ID", 0);
    ui->searchFilterComboBox->addItem("Туристы", 1);
    ui->searchFilterComboBox->addItem("Направление", 2);
    ui->searchFilterComboBox->addItem("Дата отправки", 3);
    ui->searchFilterComboBox->addItem("Длительность", 4);
    ui->searchFilterComboBox->addItem("Итоговая цена", 5);
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

    QModelIndex index = m_sortFilterModel->mapToSource(selectedIndexes.first());
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

void TouristPackageTabWidget::on_createReportButton_clicked() {
}

#include "widgets/touristtabwidget.h"
#include "ui_basetabwidget.h"

#include "models/touristtablemodel.h"
#include "dialogs/newtouristentrydialog.h"
#include "dialogs/reportdialog.h"

#include <QMessageBox>

TouristTabWidget::TouristTabWidget(DataStorage* storage, QWidget* parent) : m_dataStorage(storage),
                                                                            BaseTabWidget(
                                                                                new TouristTableModel(storage, parent),
                                                                                parent)
{
    ui->databaseTable->setSortingEnabled(true);
    ui->databaseTable->resizeColumnsToContents();
    ui->databaseTable->setWordWrap(true);
    ui->databaseTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->searchFilterComboBox->addItem("Все столбцы", -1);
    ui->searchFilterComboBox->addItem("ID", 0);
    ui->searchFilterComboBox->addItem("Имя", 1);
    ui->searchFilterComboBox->addItem("Фамилия", 2);
    ui->searchFilterComboBox->addItem("Отчество", 3);
    ui->searchFilterComboBox->addItem("Пол", 4);
    ui->searchFilterComboBox->addItem("Дата рождения", 5);
}

void TouristTabWidget::on_addEntryButton_clicked()
{
    NewTouristEntryDialog dialog(m_dataStorage->m_touristEntries.size(), this);

    if (dialog.exec())
    {
        m_dataStorage->addTouristEntry(dialog.getTouristEntry());
        reloadTable();
    }

    resizeTable();
}

void TouristTabWidget::on_editEntryButton_clicked()
{
    QModelIndexList selectedIndexes = ui->databaseTable->selectionModel()->selectedRows();

    QModelIndex index = m_sortFilterModel->mapToSource(selectedIndexes.first());
    size_t real_idx = m_dataStorage->touristEntryViewIndexToRealIndex(index.row());

    NewTouristEntryDialog dialog(
        &m_dataStorage->m_touristEntries[real_idx], this);

    if (dialog.exec())
    {
        m_dataStorage->m_touristEntries[real_idx] = dialog.getTouristEntry();
        reloadTable();
        ui->editEntryButton->setDisabled(true);
        ui->deleteEntryButton->setDisabled(true);
    }

    resizeTable();
}

void TouristTabWidget::on_deleteEntryButton_clicked()
{
    QModelIndexList selectedIndexes = ui->databaseTable->selectionModel()->selectedRows();

    QModelIndex index = m_sortFilterModel->mapToSource(selectedIndexes.first());

    if (QMessageBox::question(this, "Подтверждение удаления",
                              QString("Вы действительно хотите удалить запись?"))
        != QMessageBox::Yes)
    {
        return;
    }

    if (!index.isValid()) return;

    m_tableModel->removeEntry(index.row(), QModelIndex());

    resizeTable();
}

void TouristTabWidget::on_createReportButton_clicked()
{
    QModelIndexList selectedIndexes = ui->databaseTable->selectionModel()->selectedRows();

    QModelIndex index = m_sortFilterModel->mapToSource(selectedIndexes.first());

    if (!index.isValid()) return;

    TouristEntry entry = m_dataStorage->m_touristEntries[index.row()];


    QString reportText = QString("Данные о туристе (ID %1):\n"
            "-Имя: %2\n"
            "-Фамилия: %3\n").arg(entry.m_id.value()).
                              arg(entry.m_firstName, entry.m_lastName);

    if (!entry.m_surname.isEmpty())
    {
        reportText += QString("-Отчество: %1\n").arg(entry.m_surname);
    }
    reportText += QString("-Пол: %5\n"
        "-Дата рождения: %6\n").arg(kGenders[static_cast<size_t>(entry.m_gender)],
                                    entry.m_birthDate.toString("dd.MM.yyyy"));

    ReportDialog dialog(this, reportText);
    dialog.exec();
}

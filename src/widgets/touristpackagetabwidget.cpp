#include "widgets/touristpackagetabwidget.h"
#include "ui_basetabwidget.h"

#include "models/destinationtablemodel.h"
#include "models/touristtablemodel.h"
#include "models/touristpackagemodel.h"
#include "dialogs/newtouristpackageentrydialog.h"
#include "dialogs/reportdialog.h"
#include "dialogs/touristpackagechartdialog.h"

#include <QMessageBox>

TouristPackageTabWidget::TouristPackageTabWidget(DataStorage* storage, QWidget* parent) : m_dataStorage(storage),
    BaseTabWidget(new TouristPackageTableModel(storage, parent), parent)
{
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

    ui->showChartButton->setEnabled(true);
    connect(ui->showChartButton, &QPushButton::pressed, this, &TouristPackageTabWidget::onShowChartButtonClicked);
}

void TouristPackageTabWidget::on_addEntryButton_clicked()
{
    NewTouristPackageEntryDialog dialog(m_dataStorage->m_touristPackageEntries.size(), m_dataStorage, this);

    if (dialog.exec())
    {
        m_dataStorage->addTouristPackageEntry(dialog.getTouristPackageEntry());
        reloadTable();
    }

    resizeTable();
}

void TouristPackageTabWidget::on_editEntryButton_clicked()
{
    QModelIndexList selectedIndexes = ui->databaseTable->selectionModel()->selectedRows();

    QModelIndex index = m_sortFilterModel->mapToSource(selectedIndexes.first());
    size_t real_idx = m_dataStorage->touristPackageEntryViewIndexToRealIndex(index.row());

    NewTouristPackageEntryDialog dialog(&m_dataStorage->m_touristPackageEntries[real_idx], m_dataStorage, this);

    if (dialog.exec())
    {
        m_dataStorage->m_touristPackageEntries[real_idx] = dialog.getTouristPackageEntry();
        reloadTable();

        ui->editEntryButton->setDisabled(true);
        ui->deleteEntryButton->setDisabled(true);
    }

    resizeTable();
}

void TouristPackageTabWidget::on_deleteEntryButton_clicked()
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

void TouristPackageTabWidget::on_createReportButton_clicked()
{
    QModelIndexList selectedIndexes = ui->databaseTable->selectionModel()->selectedRows();

    QModelIndex index = m_sortFilterModel->mapToSource(selectedIndexes.first());

    if (!index.isValid()) return;

    const size_t real_idx = m_dataStorage->touristPackageEntryViewIndexToRealIndex(static_cast<size_t>(index.row()));
    if (real_idx >= static_cast<size_t>(m_dataStorage->m_touristPackageEntries.size())) return;

    TouristPackageEntry touristPackageEntry = m_dataStorage->m_touristPackageEntries[real_idx];

    QString reportText = QString("Данные о путевке (ID %1):\n"
        "Список туристов:\n").arg(touristPackageEntry.m_id.value());

    for (quint32 i = 0; i < touristPackageEntry.m_touristsIds.length(); i++)
    {
        const quint32 touristIdx = touristPackageEntry.m_touristsIds[i];
        if (touristIdx >= static_cast<quint32>(m_dataStorage->m_touristEntries.size()))
        {
            continue;
        }

        TouristEntry touristEntry = m_dataStorage->m_touristEntries[touristIdx];

        reportText += QString("    Турист %1 (ID %2):\n").arg(i + 1).arg(touristIdx);

        reportText += QString("        -Имя: %1\n"
            "        -Фамилия: %2\n").arg(touristEntry.m_firstName, touristEntry.m_lastName);

        if (!touristEntry.m_surname.isEmpty())
        {
            reportText += QString("        -Отчество: %1\n").arg(touristEntry.m_surname);
        }
        reportText += QString("        -Пол: %5\n"
            "        -Дата рождения: %6\n").arg(kGenders[static_cast<size_t>(touristEntry.m_gender)],
                                            touristEntry.m_birthDate.toString("dd.MM.yyyy"));
    }

    const quint32 destinationIdx = touristPackageEntry.m_destinationId;
    if (destinationIdx >= static_cast<quint32>(m_dataStorage->m_destinationEntries.size()))
    {
    }
    else
    {
        DestinationEntry destinationEntry = m_dataStorage->m_destinationEntries[destinationIdx];

        reportText += QString("Данные о направлении (ID %1):\n"
                "    -Страна: %2\n"
                "    -Город: %3\n"
                "    -Базовая цена: %4\n"
                "    -Тип питания: %5\n"
                "    -Кол-во звезд отеля: %6\n").arg(destinationEntry.m_id.value()).
                                               arg(destinationEntry.m_country, destinationEntry.m_city).
                                               arg(destinationEntry.m_basePrice).
                                               arg(kFoodTypes[static_cast<size_t>(destinationEntry.m_foodType)]).
                                               arg(destinationEntry.m_hotelStars);
    }

    reportText += QString("-Дата отправки: %1\n"
            "-Длительность: %2\n"
            "-Итоговая цена: %3\n").arg(touristPackageEntry.m_arrivalDate.toString("dd.MM.yyyy")).
                                   arg(touristPackageEntry.m_duration).
                                   arg(touristPackageEntry.m_finalPrice);

    ReportDialog dialog(this, reportText);
    dialog.exec();
}

void TouristPackageTabWidget::onShowChartButtonClicked()
{
    TouristPackageChartDialog dialog(m_dataStorage, this);

    dialog.exec();
}

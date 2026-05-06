#include "widgets/touristpackagetabwidget.h"
#include "ui_basetabwidget.h"

#include "models/destinationtablemodel.h"
#include "models/touristtablemodel.h"
#include "models/touristpackagemodel.h"
#include "dialogs/newtouristpackageentrydialog.h"
#include "dialogs/reportdialog.h"
#include "dialogs/touristpackagechartdialog.h"
#include "util/reportformatters.h"

TouristPackageTabWidget::TouristPackageTabWidget(DataStorage *storage, QWidget *parent)
    : BaseTabWidget(new TouristPackageTableModel(storage, parent), parent)
      , m_dataStorage(storage) {
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

void TouristPackageTabWidget::on_addEntryButton_clicked() {
    NewTouristPackageEntryDialog dialog(m_dataStorage->m_touristPackageEntries.size(), m_dataStorage, this);

    if (dialog.exec()) {
        m_dataStorage->addTouristPackageEntry(dialog.getTouristPackageEntry());
        reloadTable();
    }

    resizeTable();
}

void TouristPackageTabWidget::on_editEntryButton_clicked() {
    auto realIdx = currentSelectedRealIndex();
    if (!realIdx) return;

    NewTouristPackageEntryDialog dialog(&m_dataStorage->m_touristPackageEntries[*realIdx], m_dataStorage, this);

    if (dialog.exec()) {
        m_dataStorage->m_touristPackageEntries[*realIdx] = dialog.getTouristPackageEntry();
        reloadTable();

        ui->editEntryButton->setDisabled(true);
        ui->deleteEntryButton->setDisabled(true);
    }

    resizeTable();
}

void TouristPackageTabWidget::on_deleteEntryButton_clicked() {
    auto realIdx = currentSelectedRealIndex();
    if (!realIdx) return;

    if (!confirmDelete()) {
        return;
    }

    m_dataStorage->deleteTouristPackageEntry(*realIdx);
    afterMutation();
}

void TouristPackageTabWidget::on_createReportButton_clicked() {
    auto realIdx = currentSelectedRealIndex();
    if (!realIdx) return;

    const TouristPackageEntry &touristPackageEntry = m_dataStorage->m_touristPackageEntries[*realIdx];

    QString reportText = QString("Данные о путевке (ID %1):\n"
        "Список туристов:\n").arg(touristPackageEntry.m_id.value());

    for (quint32 i = 0; i < static_cast<quint32>(touristPackageEntry.m_touristsIds.length()); i++) {
        const quint32 touristIdx = touristPackageEntry.m_touristsIds[i];
        if (touristIdx >= static_cast<quint32>(m_dataStorage->m_touristEntries.size())) {
            continue;
        }

        const TouristEntry &touristEntry = m_dataStorage->m_touristEntries[touristIdx];

        reportText += QString("    Турист %1 (ID %2):\n").arg(i + 1).arg(touristIdx);
        reportText += ReportFormatters::formatTouristBlock(touristEntry, 8);
    }

    const quint32 destinationIdx = touristPackageEntry.m_destinationId;
    if (destinationIdx < static_cast<quint32>(m_dataStorage->m_destinationEntries.size())) {
        const DestinationEntry &destinationEntry = m_dataStorage->m_destinationEntries[destinationIdx];
        reportText += ReportFormatters::formatDestinationBlock(destinationEntry);
    }

    reportText += QString("-Дата отправки: %1\n"
            "-Длительность: %2\n"
            "-Итоговая цена: %3\n").arg(touristPackageEntry.m_arrivalDate.toString("dd.MM.yyyy")).
                                   arg(touristPackageEntry.m_duration).
                                   arg(touristPackageEntry.m_finalPrice);

    ReportDialog dialog(this, reportText);
    dialog.exec();
}

void TouristPackageTabWidget::onShowChartButtonClicked() {
    TouristPackageChartDialog dialog(m_dataStorage, this);

    dialog.exec();
}

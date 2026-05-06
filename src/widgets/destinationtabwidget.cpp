#include "widgets/destinationtabwidget.h"

#include "ui_basetabwidget.h"

#include "models/destinationtablemodel.h"
#include "dialogs/newdestinationentrydialog.h"
#include "dialogs/reportdialog.h"
#include "dialogs/destinationchartdialog.h"
#include "util/reportformatters.h"

#include <QSortFilterProxyModel>

DestinationTabWidget::DestinationTabWidget(DataStorage *storage, QWidget *parent)
    : BaseTabWidget(new DestinationTableModel(storage, parent), parent)
      , m_dataStorage(storage) {
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

    ui->showChartButton->setEnabled(true);
    connect(ui->showChartButton, &QPushButton::pressed, this, &DestinationTabWidget::onShowChartButtonClicked);
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
    auto realIdx = currentSelectedRealIndex();
    if (!realIdx) return;

    NewDestinationEntryDialog dialog(&m_dataStorage->m_destinationEntries[*realIdx], this);

    if (dialog.exec()) {
        m_dataStorage->m_destinationEntries[*realIdx] = dialog.getDestinationEntry();
        reloadTable();
        ui->editEntryButton->setDisabled(true);
        ui->deleteEntryButton->setDisabled(true);
    }

    resizeTable();
}

void DestinationTabWidget::on_deleteEntryButton_clicked() {
    auto realIdx = currentSelectedRealIndex();
    if (!realIdx) return;

    if (!confirmDelete()) {
        return;
    }

    m_dataStorage->deleteDestinationEntry(*realIdx);
    afterMutation();
}

void DestinationTabWidget::on_createReportButton_clicked() {
    auto realIdx = currentSelectedRealIndex();
    if (!realIdx) return;

    const DestinationEntry &entry = m_dataStorage->m_destinationEntries[*realIdx];

    QString reportText = ReportFormatters::formatDestinationBlock(entry);

    ReportDialog dialog(this, reportText);
    dialog.exec();
}

void DestinationTabWidget::onShowChartButtonClicked() {
    DestinationChartDialog dialog(m_dataStorage, this);

    dialog.exec();
}

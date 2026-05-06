#include "widgets/touristtabwidget.h"
#include "ui_basetabwidget.h"

#include "models/touristtablemodel.h"
#include "dialogs/newtouristentrydialog.h"
#include "dialogs/reportdialog.h"
#include "dialogs/touristchartdialog.h"
#include "util/reportformatters.h"

TouristTabWidget::TouristTabWidget(DataStorage *storage, QWidget *parent)
    : BaseTabWidget(new TouristTableModel(storage, parent), parent)
      , m_dataStorage(storage) {
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

    ui->showChartButton->setEnabled(true);
    connect(ui->showChartButton, &QPushButton::pressed, this, &TouristTabWidget::onShowChartButtonClicked);
}

void TouristTabWidget::on_addEntryButton_clicked() {
    NewTouristEntryDialog dialog(m_dataStorage->m_touristEntries.size(), this);

    if (dialog.exec()) {
        m_dataStorage->addTouristEntry(dialog.getTouristEntry());
        reloadTable();
    }

    resizeTable();
}

void TouristTabWidget::on_editEntryButton_clicked() {
    auto realIdx = currentSelectedRealIndex();
    if (!realIdx) return;

    NewTouristEntryDialog dialog(&m_dataStorage->m_touristEntries[*realIdx], this);

    if (dialog.exec()) {
        m_dataStorage->m_touristEntries[*realIdx] = dialog.getTouristEntry();
        reloadTable();
        ui->editEntryButton->setDisabled(true);
        ui->deleteEntryButton->setDisabled(true);
    }

    resizeTable();
}

void TouristTabWidget::on_deleteEntryButton_clicked() {
    auto realIdx = currentSelectedRealIndex();
    if (!realIdx) return;

    if (!confirmDelete()) {
        return;
    }

    m_dataStorage->deleteTouristEntry(*realIdx);
    afterMutation();
}

void TouristTabWidget::on_createReportButton_clicked() {
    auto realIdx = currentSelectedRealIndex();
    if (!realIdx) return;

    const TouristEntry &entry = m_dataStorage->m_touristEntries[*realIdx];

    QString reportText = QString("Данные о туристе (ID %1):\n").arg(entry.m_id.value());
    reportText += ReportFormatters::formatTouristBlock(entry);

    ReportDialog dialog(this, reportText);
    dialog.exec();
}

void TouristTabWidget::onShowChartButtonClicked() {
    TouristChartDialog dialog(m_dataStorage, this);

    dialog.exec();
}

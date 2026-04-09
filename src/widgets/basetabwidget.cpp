#include "widgets/basetabwidget.h"

#include <QMessageBox>

#include "ui_basetabwidget.h"

BaseTabWidget::BaseTabWidget(BaseTableModel *tableModel, QWidget *parent)
    : QWidget(parent)
      , ui(new Ui::BaseTabWidget)
      , m_tableModel(tableModel) {
    ui->setupUi(this);

    ui->databaseTable->setModel(m_tableModel);
    ui->databaseTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->databaseTable->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->databaseTable->selectionModel(),
        &QItemSelectionModel::selectionChanged,
        this,
        &BaseTabWidget::onSelectionChanged);
}

BaseTabWidget::~BaseTabWidget() {
    delete ui;
    delete m_tableModel;
}

void BaseTabWidget::reloadTable() {
    m_tableModel->reloadTable();
}

void BaseTabWidget::resizeTable() {
    ui->databaseTable->resizeColumnsToContents();
}

void BaseTabWidget::on_editEntryButton_clicked() {
    QMessageBox::information(this, "a", "a");
}

void BaseTabWidget::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    Q_UNUSED(deselected);

    bool hasSelection = !ui->databaseTable->selectionModel()->selectedRows().isEmpty();

    ui->deleteEntryButton->setEnabled(hasSelection);
    ui->editEntryButton->setEnabled(hasSelection);
}

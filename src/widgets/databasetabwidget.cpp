#include "widgets/databasetabwidget.h"
#include "ui_databasetabwidget.h"

DatabaseTabWidget::DatabaseTabWidget(BaseTableModel *tableModel, QWidget *parent)
    : QWidget(parent)
      , ui(new Ui::DatabaseTabWidget)
      , m_tableModel(tableModel) {
    ui->setupUi(this);

    ui->databaseTable->setModel(m_tableModel);
    ui->databaseTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->databaseTable->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->databaseTable->selectionModel(),
        &QItemSelectionModel::selectionChanged,
        this,
        &DatabaseTabWidget::onSelectionChanged);
}

DatabaseTabWidget::~DatabaseTabWidget() {
    delete ui;
    delete m_tableModel;
}

void DatabaseTabWidget::reloadTable() {
    m_tableModel->reloadTable();
}

void DatabaseTabWidget::resizeTable() {
    ui->databaseTable->resizeColumnsToContents();
}

void DatabaseTabWidget::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    Q_UNUSED(deselected);

    bool hasSelection = !ui->databaseTable->selectionModel()->selectedRows().isEmpty();

    ui->deleteEntryButton->setEnabled(hasSelection);
}

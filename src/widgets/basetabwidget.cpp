#include "widgets/basetabwidget.h"
#include "ui_basetabwidget.h"

#include <QMessageBox>

BaseTabWidget::BaseTabWidget(BaseTableModel *tableModel, QWidget *parent)
    : QWidget(parent)
      , ui(new Ui::BaseTabWidget)
      , m_tableModel(tableModel) {
    ui->setupUi(this);

    m_sortFilterModel = new QSortFilterProxyModel(this);
    m_sortFilterModel->setSourceModel(m_tableModel);
    m_sortFilterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    m_sortFilterModel->setFilterKeyColumn(-1);
    m_sortFilterModel->setFilterFixedString("");

    ui->databaseTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->databaseTable->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->databaseTable->setModel(m_sortFilterModel);
    m_sortFilterModel->setSortRole(Qt::EditRole);
    ui->databaseTable->sortByColumn(0, Qt::AscendingOrder);

    connect(ui->databaseTable->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &BaseTabWidget::onSelectionChanged);
}

BaseTabWidget::~BaseTabWidget() {
    delete ui;
    delete m_tableModel;
    delete m_sortFilterModel;
}

void BaseTabWidget::reloadTable() {
    m_tableModel->reloadTable();
}

void BaseTabWidget::resizeTable() {
    ui->databaseTable->resizeColumnsToContents();
}

void BaseTabWidget::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    Q_UNUSED(deselected);

    bool hasSelection = !ui->databaseTable->selectionModel()->selectedRows().isEmpty();

    ui->deleteEntryButton->setEnabled(hasSelection);
    ui->editEntryButton->setEnabled(hasSelection);
}

void BaseTabWidget::on_searchFilterComboBox_currentIndexChanged(int index)
{
    int column = ui->searchFilterComboBox->itemData(index).toInt();
    m_sortFilterModel->setFilterKeyColumn(column);

    resizeTable();
}


void BaseTabWidget::on_searchFilterLineEdit_textChanged(const QString &text)
{
    if (text.isEmpty())
    {
        ui->resetFilterPushButton->setDisabled(true);
    }
    else
    {
        ui->resetFilterPushButton->setEnabled(true);
    }

    m_sortFilterModel->setFilterFixedString(text);

    resizeTable();
}


void BaseTabWidget::on_resetFilterPushButton_clicked()
{
    ui->searchFilterLineEdit->clear();
}


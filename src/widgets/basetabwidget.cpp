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

std::optional<size_t> BaseTabWidget::currentSelectedRealIndex() {
    QModelIndexList selectedIndexes = ui->databaseTable->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) return std::nullopt;

    QModelIndex index = m_sortFilterModel->mapToSource(selectedIndexes.first());
    if (!index.isValid()) return std::nullopt;

    return m_tableModel->viewIndexToRealIndex(static_cast<size_t>(index.row()));
}

bool BaseTabWidget::confirmDelete() {
    return QMessageBox::question(this, "Подтверждение удаления",
                                 QString("Вы действительно хотите удалить запись?")) == QMessageBox::Yes;
}

void BaseTabWidget::afterMutation() {
    reloadTable();
    resizeTable();
}

void BaseTabWidget::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    Q_UNUSED(selected);
    Q_UNUSED(deselected);

    bool hasSelection = !ui->databaseTable->selectionModel()->selectedRows().isEmpty();

    ui->deleteEntryButton->setEnabled(hasSelection);
    ui->editEntryButton->setEnabled(hasSelection);
    ui->createReportButton->setEnabled(hasSelection);
}

void BaseTabWidget::on_searchFilterComboBox_currentIndexChanged(int index) {
    int column = ui->searchFilterComboBox->itemData(index).toInt();
    m_sortFilterModel->setFilterKeyColumn(column);

    resizeTable();
}


void BaseTabWidget::on_searchFilterLineEdit_textChanged(const QString &text) {
    if (text.isEmpty()) {
        ui->resetFilterPushButton->setDisabled(true);
    } else {
        ui->resetFilterPushButton->setEnabled(true);
    }

    m_sortFilterModel->setFilterFixedString(text);

    resizeTable();
}


void BaseTabWidget::on_resetFilterPushButton_clicked() {
    ui->searchFilterLineEdit->clear();
}

#include "dialogs/entryselectiondialog.h"
#include "ui_entryselectiondialog.h"

EntrySelectionDialog::EntrySelectionDialog(bool isSingleSelection, BaseTableModel *tableModel, QWidget *parent)
    : QDialog(parent)
      , ui(new Ui::EntrySelectionDialog)
      , m_tableModel(tableModel)
      , m_isSingleSelection(isSingleSelection) {
    ui->setupUi(this);

    ui->databaseTable->setModel(m_tableModel);
    ui->databaseTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    if (isSingleSelection) {
        ui->databaseTable->setSelectionMode(QAbstractItemView::SingleSelection);
    }

    connect(ui->databaseTable->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &EntrySelectionDialog::onSelectionChanged);
}

EntrySelectionDialog::~EntrySelectionDialog() {
    delete ui;
}

QList<quint32> EntrySelectionDialog::getChosenIndexes() {
    assert(!m_isSingleSelection);

    QList<quint32> indexes;
    for (auto selection: ui->databaseTable->selectionModel()->selectedRows()) {
        indexes.append(m_tableModel->viewIndexToRealIndex(selection.row()));
    }

    return indexes;
}

quint32 EntrySelectionDialog::getChosenIndex() {
    assert(m_isSingleSelection);

    return m_tableModel->viewIndexToRealIndex(ui->databaseTable->selectionModel()->selectedRows()[0].row());
}

void EntrySelectionDialog::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    Q_UNUSED(deselected);

    bool hasSelection = !ui->databaseTable->selectionModel()->selectedRows().isEmpty();

    ui->addDestinationSelectionButton->setEnabled(hasSelection);
}

void EntrySelectionDialog::on_addDestinationSelectionButton_clicked() {
    accept();
}


void EntrySelectionDialog::on_cancelDestinationSelectionButton_clicked() {
    reject();
}

#include "widgets/databasetabwidget.h"
#include "ui_databasetabwidget.h"

DatabaseTabWidget::DatabaseTabWidget(BaseTableModel *tableModel, QWidget *parent)
    : QWidget(parent)
      , ui(new Ui::DatabaseTabWidget)
      , m_tableModel(tableModel) {
    ui->setupUi(this);
}

DatabaseTabWidget::~DatabaseTabWidget() {
    delete ui;
    delete m_tableModel;
}

void DatabaseTabWidget::reloadTable() {
    m_tableModel->reloadTable();
}

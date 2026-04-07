#include "widgets/databasetabwidget.h"
#include "ui_databasetabwidget.h"

DatabaseTabWidget::DatabaseTabWidget(QWidget *parent)
    : QWidget(parent)
      , ui(new Ui::DatabaseTabWidget) {
    ui->setupUi(this);
}

DatabaseTabWidget::~DatabaseTabWidget() {
    delete ui;
}

void DatabaseTabWidget::on_addEntryButton_clicked() {
    onAddEntryButtonClicked();
}


void DatabaseTabWidget::on_deleteEntryButton_clicked() {
    onDeleteEntryButtonClicked();
}


void DatabaseTabWidget::on_createReportButton_clicked() {
    onCreateReportButtonClicked();
}

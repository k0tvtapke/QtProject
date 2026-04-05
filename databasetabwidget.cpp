#include "databasetabwidget.h"
#include "ui_databasetabwidget.h"

DatabaseTabWidget::DatabaseTabWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DatabaseTabWidget)
{
    ui->setupUi(this);
}

DatabaseTabWidget::~DatabaseTabWidget()
{
    delete ui;
}

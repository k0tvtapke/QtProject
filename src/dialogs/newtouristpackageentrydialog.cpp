#include "dialogs/newtouristpackageentrydialog.h"
#include "ui_newtouristpackageentrydialog.h"

NewTouristPackageEntryDialog::NewTouristPackageEntryDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewTouristPackageEntryDialog)
{
    ui->setupUi(this);
}

NewTouristPackageEntryDialog::~NewTouristPackageEntryDialog()
{
    delete ui;
}

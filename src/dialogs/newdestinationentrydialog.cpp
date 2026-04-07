#include "dialogs/newdestinationentrydialog.h"
#include "ui_newdestinationentrydialog.h"

NewDestinationEntryDialog::NewDestinationEntryDialog(size_t id, QWidget *parent)
    : QDialog(parent)
      , ui(new Ui::NewDestinationEntryDialog)
      , m_destination_entry(new DestinationEntry) {
    ui->setupUi(this);

    this->setWindowTitle("Добавить новое направление");
    ui->idLineEdit->setText(QString::number(id));
}

NewDestinationEntryDialog::~NewDestinationEntryDialog() {
    delete ui;
    delete m_destination_entry;
}

DestinationEntry NewDestinationEntryDialog::getDestinationEntry() const {
    return *m_destination_entry;
}

void NewDestinationEntryDialog::on_addEntryButton_clicked() {
    m_destination_entry->m_country = ui->countryLineEdit->text();
    m_destination_entry->m_city = ui->cityLineEdit->text();
    m_destination_entry->m_basePrice = ui->basePriceDoubleSpinBox->value();
    m_destination_entry->m_foodType = static_cast<FoodType>(ui->foodTypeComboBox->currentIndex());
    m_destination_entry->m_hotelStars = ui->hotelStarsSpinBox->value();

    accept();
}


void NewDestinationEntryDialog::on_cancelButton_clicked() {
    reject();
}

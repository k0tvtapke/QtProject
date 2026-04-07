#include "dialogs/newtouristentrydialog.h"
#include "ui_newtouristentrydialog.h"

NewTouristEntryDialog::NewTouristEntryDialog(size_t id, QWidget *parent)
    : QDialog(parent)
      , ui(new Ui::NewTouristEntryDialog)
      , m_touristEntry(new TouristEntry) {
    ui->setupUi(this);

    this->setWindowTitle("Добавить нового туриста");
    ui->idLineEdit->setText(QString::number(id));
}

NewTouristEntryDialog::~NewTouristEntryDialog() {
    delete ui;
    delete m_touristEntry;
}

TouristEntry NewTouristEntryDialog::getTouristEntry() const {
    return *m_touristEntry;
}

void NewTouristEntryDialog::on_addEntryButton_clicked() {
    m_touristEntry->m_firstName = ui->firstNameLineEdit->text();
    m_touristEntry->m_lastName = ui->lastNameLineEdit->text();
    m_touristEntry->m_surname = ui->surnameLineEdit->text();
    m_touristEntry->m_gender = static_cast<Gender>(ui->genderComboBox->currentIndex());
    m_touristEntry->m_birthDate = ui->birthDateDateEdit->date();

    accept();
}


void NewTouristEntryDialog::on_cancelButton_clicked() {
    reject();
}

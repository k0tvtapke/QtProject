#include "dialogs/newtouristentrydialog.h"
#include "ui_newtouristentrydialog.h"

NewTouristEntryDialog::NewTouristEntryDialog(size_t id, QWidget *parent)
    : QDialog(parent)
      , ui(new Ui::NewTouristEntryDialog)
      , m_touristEntry(new TouristEntry) {
    ui->setupUi(this);

    isNew = true;

    this->setWindowTitle("Добавить нового туриста");
    ui->idLineEdit->setText(QString::number(id));
}

NewTouristEntryDialog::NewTouristEntryDialog(TouristEntry *touristEntry, QWidget *parent)
    : QDialog(parent)
      , ui(new Ui::NewTouristEntryDialog)
      , m_touristEntry(touristEntry) {
    ui->setupUi(this);

    isNew = false;

    this->setWindowTitle("Изменить туриста");
    ui->idLineEdit->setText(QString::number(m_touristEntry->m_id.value()));

    ui->firstNameLineEdit->setText(m_touristEntry->m_firstName);
    ui->lastNameLineEdit->setText(m_touristEntry->m_lastName);
    ui->surnameLineEdit->setText(m_touristEntry->m_surname);
    ui->genderComboBox->setCurrentIndex(static_cast<int>(m_touristEntry->m_gender));
    ui->birthDateDateEdit->setDate(m_touristEntry->m_birthDate);

    ui->addEntryButton->setText("Изменить запись");
    ui->addEntryButton->setEnabled(true);
}

NewTouristEntryDialog::~NewTouristEntryDialog() {
    delete ui;
    if (isNew) {
        delete m_touristEntry;
    }
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

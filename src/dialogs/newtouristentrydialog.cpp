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

    QRegularExpression nameRe("^[А-ЯЁ][а-яё]*$");
    ui->firstNameLineEdit->setValidator(new QRegularExpressionValidator(nameRe, this));
    ui->lastNameLineEdit->setValidator(new QRegularExpressionValidator(nameRe, this));

    QRegularExpression surnameRe("^([А-ЯЁ][а-яё]*)?$");
    ui->surnameLineEdit->setValidator(new QRegularExpressionValidator(surnameRe, this));

    ui->addEntryButton->setDisabled(true);

    connect(ui->firstNameLineEdit, &QLineEdit::textEdited, this, &NewTouristEntryDialog::onLineEditChanged);
    connect(ui->lastNameLineEdit, &QLineEdit::textEdited, this, &NewTouristEntryDialog::onLineEditChanged);
    connect(ui->surnameLineEdit, &QLineEdit::textEdited, this, &NewTouristEntryDialog::onLineEditChanged);
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

    QRegularExpression nameRe("^[А-ЯЁ][а-яё]*$");
    ui->firstNameLineEdit->setValidator(new QRegularExpressionValidator(nameRe, this));
    ui->lastNameLineEdit->setValidator(new QRegularExpressionValidator(nameRe, this));

    QRegularExpression surnameRe("^([А-ЯЁ][а-яё]*)?$");
    ui->surnameLineEdit->setValidator(new QRegularExpressionValidator(surnameRe, this));

    connect(ui->firstNameLineEdit, &QLineEdit::textEdited, this, &NewTouristEntryDialog::onLineEditChanged);
    connect(ui->lastNameLineEdit, &QLineEdit::textEdited, this, &NewTouristEntryDialog::onLineEditChanged);
    connect(ui->surnameLineEdit, &QLineEdit::textEdited, this, &NewTouristEntryDialog::onLineEditChanged);
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

void NewTouristEntryDialog::onLineEditChanged()
{
    int flagsSum = 0;
    if (ui->firstNameLineEdit->hasAcceptableInput())
    {
        ui->firstNameLineEdit->setStyleSheet("");
        flagsSum++;
    }
    else
    {
        ui->firstNameLineEdit->setStyleSheet("border: 1px solid red;");
    }
    if (ui->lastNameLineEdit->hasAcceptableInput())
    {
        ui->lastNameLineEdit->setStyleSheet("");
        flagsSum++;
    }
    else
    {
        ui->lastNameLineEdit->setStyleSheet("border: 1px solid red;");
    }
    if (ui->surnameLineEdit->hasAcceptableInput())
    {
        ui->surnameLineEdit->setStyleSheet("");
        flagsSum++;
    }
    else
    {
        ui->surnameLineEdit->setStyleSheet("border: 1px solid red;");
    }

    if (flagsSum == 3)
    {
        ui->addEntryButton->setEnabled(true);
    }
    else
    {
        ui->addEntryButton->setDisabled(true);
    }
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

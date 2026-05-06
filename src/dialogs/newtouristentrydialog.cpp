#include "dialogs/newtouristentrydialog.h"
#include "ui_newtouristentrydialog.h"

namespace {
    const QString kNameTooltip =
        "Только кириллица, начинается с заглавной буквы, далее — строчные. Пример: «Иван».";
    const QString kSurnameTooltip =
        "Необязательное поле. Если заполнено — только кириллица, начинается с заглавной буквы. "
        "Пример: «Иванович».";
}

NewTouristEntryDialog::NewTouristEntryDialog(size_t id, QWidget *parent)
    : BaseEntryDialog(parent)
      , m_touristEntry(new TouristEntry)
      , ui(new Ui::NewTouristEntryDialog) {
    ui->setupUi(this);

    isNew = true;

    this->setWindowTitle("Добавить нового туриста");
    ui->idLineEdit->setText(QString::number(id));

    ui->birthDateDateEdit->setCalendarPopup(true);

    setupValidators();

    ui->addEntryButton->setDisabled(true);
    ui->addEntryButton->setToolTip("Заполните корректно все поля");
}

NewTouristEntryDialog::NewTouristEntryDialog(TouristEntry *touristEntry, QWidget *parent)
    : BaseEntryDialog(parent)
      , m_touristEntry(touristEntry)
      , ui(new Ui::NewTouristEntryDialog) {
    ui->setupUi(this);

    isNew = false;

    this->setWindowTitle("Изменить туриста");
    ui->idLineEdit->setText(QString::number(m_touristEntry->m_id.value()));

    ui->birthDateDateEdit->setCalendarPopup(true);

    ui->firstNameLineEdit->setText(m_touristEntry->m_firstName);
    ui->lastNameLineEdit->setText(m_touristEntry->m_lastName);
    ui->surnameLineEdit->setText(m_touristEntry->m_surname);
    ui->genderComboBox->setCurrentIndex(static_cast<int>(m_touristEntry->m_gender));
    ui->birthDateDateEdit->setDate(m_touristEntry->m_birthDate);

    ui->addEntryButton->setText("Изменить запись");

    setupValidators();
    revalidate();
}

NewTouristEntryDialog::~NewTouristEntryDialog() {
    delete ui;
    if (isNew) {
        delete m_touristEntry;
    }
}

void NewTouristEntryDialog::setupValidators() {
    QRegularExpression nameRe("^[А-ЯЁ][а-яё]*$");
    registerValidatedField(ui->firstNameLineEdit, nameRe, "Имя", kNameTooltip);
    registerValidatedField(ui->lastNameLineEdit, nameRe, "Фамилия", kNameTooltip);

    QRegularExpression surnameRe("^([А-ЯЁ][а-яё]*)?$");
    registerValidatedField(ui->surnameLineEdit, surnameRe, "Отчество", kSurnameTooltip);

    setSubmitButton(ui->addEntryButton);
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

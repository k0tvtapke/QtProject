#include "dialogs/newdestinationentrydialog.h"
#include "ui_newdestinationentrydialog.h"

namespace {
    const QString kPlaceTooltip =
        "Только кириллица. Слова начинаются с заглавной буквы, "
        "разделяются пробелом, дефисом или апострофом.";
}

NewDestinationEntryDialog::NewDestinationEntryDialog(size_t id, QWidget* parent)
    : BaseEntryDialog(parent)
      , m_destination_entry(new DestinationEntry)
      , ui(new Ui::NewDestinationEntryDialog) {
    ui->setupUi(this);

    isNew = true;

    this->setWindowTitle("Добавить новое направление");
    ui->idLineEdit->setText(QString::number(id));

    setupValidators();

    ui->addEntryButton->setDisabled(true);
    ui->addEntryButton->setToolTip("Заполните корректно все поля");
}

NewDestinationEntryDialog::NewDestinationEntryDialog(DestinationEntry* destinationEntry, QWidget* parent)
    : BaseEntryDialog(parent)
      , m_destination_entry(destinationEntry)
      , ui(new Ui::NewDestinationEntryDialog) {
    ui->setupUi(this);

    isNew = false;

    this->setWindowTitle("Изменить направление");

    ui->idLineEdit->setText(QString::number(m_destination_entry->m_id.value()));
    ui->countryLineEdit->setText(m_destination_entry->m_country);
    ui->cityLineEdit->setText(m_destination_entry->m_city);
    ui->basePriceDoubleSpinBox->setValue(m_destination_entry->m_basePrice);
    ui->foodTypeComboBox->setCurrentIndex(static_cast<int>(m_destination_entry->m_foodType));
    ui->hotelStarsSpinBox->setValue(m_destination_entry->m_hotelStars);

    ui->addEntryButton->setText("Изменить запись");

    setupValidators();
    revalidate();
}

NewDestinationEntryDialog::~NewDestinationEntryDialog() {
    delete ui;
    if (isNew) {
        delete m_destination_entry;
    }
}

void NewDestinationEntryDialog::setupValidators() {
    QRegularExpression placeRe("^[А-ЯЁ][а-яё]*([ \\-'][А-ЯЁа-яё][а-яё]*)*$");
    registerValidatedField(ui->countryLineEdit, placeRe, "Страна", kPlaceTooltip);
    registerValidatedField(ui->cityLineEdit, placeRe, "Город", kPlaceTooltip);
    setSubmitButton(ui->addEntryButton);
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

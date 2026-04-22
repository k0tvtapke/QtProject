#include "dialogs/newdestinationentrydialog.h"
#include "ui_newdestinationentrydialog.h"

NewDestinationEntryDialog::NewDestinationEntryDialog(size_t id, QWidget* parent)
    : QDialog(parent)
      , ui(new Ui::NewDestinationEntryDialog)
      , m_destination_entry(new DestinationEntry)
{
    ui->setupUi(this);

    isNew = true;

    this->setWindowTitle("Добавить новое направление");
    ui->idLineEdit->setText(QString::number(id));

    QRegularExpression placeRe("^[А-ЯЁ][а-яё]*([ \\-'][А-ЯЁа-яё][а-яё]*)*$");
    ui->countryLineEdit->setValidator(new QRegularExpressionValidator(placeRe, this));
    ui->cityLineEdit->setValidator(new QRegularExpressionValidator(placeRe, this));

    ui->addEntryButton->setDisabled(true);

    connect(ui->countryLineEdit, &QLineEdit::textEdited, this, &NewDestinationEntryDialog::onLineEditChanged);
    connect(ui->cityLineEdit, &QLineEdit::textEdited, this, &NewDestinationEntryDialog::onLineEditChanged);
}

NewDestinationEntryDialog::NewDestinationEntryDialog(DestinationEntry* destinationEntry, QWidget* parent)
    : QDialog(parent)
      , ui(new Ui::NewDestinationEntryDialog)
      , m_destination_entry(destinationEntry)
{
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
    ui->addEntryButton->setEnabled(true);

    QRegularExpression placeRe("^[А-ЯЁ][а-яё]*([ \\-'][А-ЯЁа-яё][а-яё]*)*$");
    ui->countryLineEdit->setValidator(new QRegularExpressionValidator(placeRe, this));
    ui->cityLineEdit->setValidator(new QRegularExpressionValidator(placeRe, this));

    connect(ui->countryLineEdit, &QLineEdit::textEdited, this, &NewDestinationEntryDialog::onLineEditChanged);
    connect(ui->cityLineEdit, &QLineEdit::textEdited, this, &NewDestinationEntryDialog::onLineEditChanged);

}

NewDestinationEntryDialog::~NewDestinationEntryDialog()
{
    delete ui;
    if (isNew)
    {
        delete m_destination_entry;
    }
}

DestinationEntry NewDestinationEntryDialog::getDestinationEntry() const
{
    return *m_destination_entry;
}

void NewDestinationEntryDialog::onLineEditChanged()
{
    int flagsSum = 0;
    if (ui->countryLineEdit->hasAcceptableInput())
    {
        ui->countryLineEdit->setStyleSheet("");
        flagsSum++;
    }
    else
    {
        ui->countryLineEdit->setStyleSheet("border: 1px solid red;");
    }
    if (ui->cityLineEdit->hasAcceptableInput())
    {
        ui->cityLineEdit->setStyleSheet("");
        flagsSum++;
    }
    else
    {
        ui->cityLineEdit->setStyleSheet("border: 1px solid red;");
    }

    if (flagsSum == 2)
    {
        ui->addEntryButton->setEnabled(true);
    }
    else
    {
        ui->addEntryButton->setDisabled(true);
    }
}

void NewDestinationEntryDialog::on_addEntryButton_clicked()
{
    m_destination_entry->m_country = ui->countryLineEdit->text();
    m_destination_entry->m_city = ui->cityLineEdit->text();
    m_destination_entry->m_basePrice = ui->basePriceDoubleSpinBox->value();
    m_destination_entry->m_foodType = static_cast<FoodType>(ui->foodTypeComboBox->currentIndex());
    m_destination_entry->m_hotelStars = ui->hotelStarsSpinBox->value();

    accept();
}


void NewDestinationEntryDialog::on_cancelButton_clicked()
{
    reject();
}

#include "dialogs/newtouristpackageentrydialog.h"
#include "ui_newtouristpackageentrydialog.h"

#include "models/touristtablemodel.h"
#include "models/destinationtablemodel.h"
#include "dialogs/entryselectiondialog.h"

NewTouristPackageEntryDialog::NewTouristPackageEntryDialog(size_t id, DataStorage* dataStorage, QWidget* parent)
    : QDialog(parent)
      , ui(new Ui::NewTouristPackageEntryDialog)
      , m_dataStorage(dataStorage)
      , m_touristPackageEntry(new TouristPackageEntry)
{
    ui->setupUi(this);

    isNew = true;

    this->setWindowTitle("Добавить новую путевку");
    ui->idLineEdit->setText(QString::number(id));

    ui->addEntryButton->setDisabled(true);
}

NewTouristPackageEntryDialog::NewTouristPackageEntryDialog(TouristPackageEntry* touristPackageEntry,
                                                           DataStorage* dataStorage, QWidget* parent)
    : QDialog(parent)
      , ui(new Ui::NewTouristPackageEntryDialog)
      , m_dataStorage(dataStorage)
      , m_touristPackageEntry(touristPackageEntry)
{
    ui->setupUi(this);

    isNew = false;

    this->setWindowTitle("Изменить путевку");

    ui->idLineEdit->setText(QString::number(m_touristPackageEntry->m_id.value()));

    m_touristsIds = m_touristPackageEntry->m_touristsIds;
    QString labelText = "ID выбранных туристов: ";
    for (auto id : m_touristsIds)
    {
        if (m_dataStorage->m_touristEntries[id].m_surname.isEmpty())
        {
            labelText += QString("\n    %1 %2 (ID %3)").arg(
                m_dataStorage->m_touristEntries[id].m_lastName,
                m_dataStorage->m_touristEntries[id].m_firstName,
                QString::number(id));
        }
        else
        {
            labelText += QString("\n    %1 %2 %3 (ID %4)").arg(
                m_dataStorage->m_touristEntries[id].m_lastName,
                m_dataStorage->m_touristEntries[id].m_firstName,
                m_dataStorage->m_touristEntries[id].m_surname,
                QString::number(id));
        }
    }
    ui->chosenTouristsLabel->setText(labelText);

    m_destinationId = touristPackageEntry->m_destinationId;
    ui->chosenDestinationLabel->setText(QString("Выбранное направление:\n"
        "    %1, %2 (ID %3)\n"
        "    Базовая цена: %4").arg(m_dataStorage->m_destinationEntries[m_destinationId.value()].m_country,
                                    m_dataStorage->m_destinationEntries[m_destinationId.value()].m_city,
                                    QString::number(m_destinationId.value()),
                                    QString::number(
                                        m_dataStorage->m_destinationEntries[m_destinationId.value()].m_basePrice)));

    ui->arrivalDateDateEdit->setDate(m_touristPackageEntry->m_arrivalDate);
    ui->durationSpinBox->setValue(m_touristPackageEntry->m_duration);
    ui->finalPriceDoubleSpinBox->setValue(m_touristPackageEntry->m_finalPrice);

    ui->addEntryButton->setText("Изменить запись");
    ui->addEntryButton->setEnabled(true);
}

NewTouristPackageEntryDialog::~NewTouristPackageEntryDialog()
{
    delete ui;
    if (isNew)
    {
        delete m_touristPackageEntry;
    }
}

TouristPackageEntry NewTouristPackageEntryDialog::getTouristPackageEntry() const
{
    return *m_touristPackageEntry;
}

void NewTouristPackageEntryDialog::on_addEntryButton_clicked()
{
    m_touristPackageEntry->m_touristsIds = m_touristsIds;
    m_touristPackageEntry->m_destinationId = m_destinationId.value();
    m_touristPackageEntry->m_arrivalDate = ui->arrivalDateDateEdit->date();
    m_touristPackageEntry->m_duration = ui->durationSpinBox->value();
    m_touristPackageEntry->m_finalPrice = ui->finalPriceDoubleSpinBox->value();

    accept();
}


void NewTouristPackageEntryDialog::on_cancelButton_clicked()
{
    reject();
}

void NewTouristPackageEntryDialog::on_chooseTouristButton_clicked()
{
    TouristTableModel tableModel(m_dataStorage, this);

    EntrySelectionDialog entry_selection_dialog(false, &tableModel);

    if (entry_selection_dialog.exec())
    {
        m_touristsIds = entry_selection_dialog.getChosenIndexes();

        QString labelText = "ID выбранных туристов: ";
        for (auto id : m_touristsIds)
        {
            if (m_dataStorage->m_touristEntries[id].m_surname.isEmpty())
            {
                labelText += QString("\n    %1 %2 (ID %3)").arg(
                    m_dataStorage->m_touristEntries[id].m_lastName,
                    m_dataStorage->m_touristEntries[id].m_firstName,
                    QString::number(id));
            }
            else
            {
                labelText += QString("\n    %1 %2 %3 (ID %4)").arg(
                    m_dataStorage->m_touristEntries[id].m_lastName,
                    m_dataStorage->m_touristEntries[id].m_firstName,
                    m_dataStorage->m_touristEntries[id].m_surname,
                    QString::number(id));
            }
        }
        ui->chosenTouristsLabel->setText(labelText);
    }

    checkIfAcceptable();
}


void NewTouristPackageEntryDialog::on_chooseDestinationButton_clicked()
{
    DestinationTableModel tableModel(m_dataStorage, this);

    EntrySelectionDialog entry_selection_dialog(true, &tableModel);

    if (entry_selection_dialog.exec())
    {
        m_destinationId = entry_selection_dialog.getChosenIndex();

        ui->chosenDestinationLabel->setText(QString("Выбранное направление:\n"
        "    %1, %2 (ID %3)\n"
        "    Базовая цена: %4").arg(m_dataStorage->m_destinationEntries[m_destinationId.value()].m_country,
                                    m_dataStorage->m_destinationEntries[m_destinationId.value()].m_city,
                                    QString::number(m_destinationId.value()),
                                    QString::number(
                                        m_dataStorage->m_destinationEntries[m_destinationId.value()].m_basePrice)));
    }

    checkIfAcceptable();
}

void NewTouristPackageEntryDialog::checkIfAcceptable()
{
    if (!m_touristsIds.isEmpty() && m_destinationId.has_value())
    {
        ui->addEntryButton->setEnabled(true);
    }
}

#include "dialogs/newtouristpackageentrydialog.h"
#include "ui_newtouristpackageentrydialog.h"

#include "models/touristtablemodel.h"
#include "models/destinationtablemodel.h"
#include "dialogs/entryselectiondialog.h"

NewTouristPackageEntryDialog::NewTouristPackageEntryDialog(size_t id, DataStorage* dataStorage, QWidget* parent)
    : BaseEntryDialog(parent)
      , m_dataStorage(dataStorage)
      , m_touristPackageEntry(new TouristPackageEntry)
      , ui(new Ui::NewTouristPackageEntryDialog) {
    ui->setupUi(this);

    isNew = true;

    this->setWindowTitle("Добавить новую путевку");
    ui->idLineEdit->setText(QString::number(id));

    ui->arrivalDateDateEdit->setCalendarPopup(true);
    ui->arrivalDateDateEdit->setDate(QDate::currentDate());

    ui->addEntryButton->setDisabled(true);
    ui->addEntryButton->setToolTip("Выберите туристов и направление");

    setSubmitButton(ui->addEntryButton);
}

NewTouristPackageEntryDialog::NewTouristPackageEntryDialog(TouristPackageEntry* touristPackageEntry,
                                                           DataStorage* dataStorage, QWidget* parent)
    : BaseEntryDialog(parent)
      , m_dataStorage(dataStorage)
      , m_touristPackageEntry(touristPackageEntry)
      , ui(new Ui::NewTouristPackageEntryDialog) {
    ui->setupUi(this);

    isNew = false;

    this->setWindowTitle("Изменить путевку");

    ui->idLineEdit->setText(QString::number(m_touristPackageEntry->m_id.value()));

    m_touristsIds = m_touristPackageEntry->m_touristsIds;
    refreshChosenTouristsLabel();

    m_destinationId = touristPackageEntry->m_destinationId;
    refreshChosenDestinationLabel();

    ui->arrivalDateDateEdit->setCalendarPopup(true);
    ui->arrivalDateDateEdit->setDate(m_touristPackageEntry->m_arrivalDate);
    ui->durationSpinBox->setValue(m_touristPackageEntry->m_duration);
    ui->finalPriceDoubleSpinBox->setValue(m_touristPackageEntry->m_finalPrice);

    ui->addEntryButton->setText("Изменить запись");
    ui->addEntryButton->setEnabled(true);

    setSubmitButton(ui->addEntryButton);
    revalidate();
}

NewTouristPackageEntryDialog::~NewTouristPackageEntryDialog() {
    delete ui;
    if (isNew) {
        delete m_touristPackageEntry;
    }
}

TouristPackageEntry NewTouristPackageEntryDialog::getTouristPackageEntry() const {
    return *m_touristPackageEntry;
}

bool NewTouristPackageEntryDialog::additionalAcceptanceCheck() const {
    return !m_touristsIds.isEmpty() && m_destinationId.has_value();
}

void NewTouristPackageEntryDialog::refreshChosenTouristsLabel() {
    QString labelText = "ID выбранных туристов: ";
    for (auto id : m_touristsIds) {
        if (id >= static_cast<quint32>(m_dataStorage->m_touristEntries.size())) {
            continue;
        }

        const auto &t = m_dataStorage->m_touristEntries[id];
        if (t.m_surname.isEmpty()) {
            labelText += QString("\n    %1 %2 (ID %3)").arg(t.m_lastName, t.m_firstName, QString::number(id));
        } else {
            labelText += QString("\n    %1 %2 %3 (ID %4)").arg(
                t.m_lastName, t.m_firstName, t.m_surname, QString::number(id));
        }
    }
    ui->chosenTouristsLabel->setText(labelText);
}

void NewTouristPackageEntryDialog::refreshChosenDestinationLabel() {
    if (!m_destinationId.has_value() ||
        m_destinationId.value() >= static_cast<quint32>(m_dataStorage->m_destinationEntries.size())) {
        ui->chosenDestinationLabel->setText(QString("Выбранное направление:\n    "));
        return;
    }

    const auto &d = m_dataStorage->m_destinationEntries[m_destinationId.value()];
    ui->chosenDestinationLabel->setText(QString("Выбранное направление:\n"
            "    %1, %2 (ID %3)\n"
            "    Базовая цена: %4").arg(d.m_country,
                                        d.m_city,
                                        QString::number(m_destinationId.value()),
                                        QString::number(d.m_basePrice)));
}

void NewTouristPackageEntryDialog::on_addEntryButton_clicked() {
    m_touristPackageEntry->m_touristsIds = m_touristsIds;
    m_touristPackageEntry->m_destinationId = m_destinationId.value();
    m_touristPackageEntry->m_arrivalDate = ui->arrivalDateDateEdit->date();
    m_touristPackageEntry->m_duration = ui->durationSpinBox->value();
    m_touristPackageEntry->m_finalPrice = ui->finalPriceDoubleSpinBox->value();

    accept();
}


void NewTouristPackageEntryDialog::on_cancelButton_clicked() {
    reject();
}

void NewTouristPackageEntryDialog::on_chooseTouristButton_clicked() {
    TouristTableModel tableModel(m_dataStorage, this);

    EntrySelectionDialog entry_selection_dialog(false, &tableModel);

    if (entry_selection_dialog.exec()) {
        m_touristsIds = entry_selection_dialog.getChosenIndexes();
        refreshChosenTouristsLabel();
    }

    revalidate();
}


void NewTouristPackageEntryDialog::on_chooseDestinationButton_clicked() {
    DestinationTableModel tableModel(m_dataStorage, this);

    EntrySelectionDialog entry_selection_dialog(true, &tableModel);

    if (entry_selection_dialog.exec()) {
        m_destinationId = entry_selection_dialog.getChosenIndex();
        refreshChosenDestinationLabel();
    }

    revalidate();
}

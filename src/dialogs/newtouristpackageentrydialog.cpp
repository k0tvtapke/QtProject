#include "dialogs/newtouristpackageentrydialog.h"
#include "ui_newtouristpackageentrydialog.h"

#include "models/touristtablemodel.h"
#include "models/destinationtablemodel.h"
#include "dialogs/entryselectiondialog.h"

NewTouristPackageEntryDialog::NewTouristPackageEntryDialog(size_t id, DataStorage *dataStorage, QWidget *parent)
    : QDialog(parent)
      , ui(new Ui::NewTouristPackageEntryDialog)
      , m_dataStorage(dataStorage)
      , m_touristPackageEntry(new TouristPackageEntry){
    ui->setupUi(this);

    isNew = true;

    this->setWindowTitle("Добавить новую путевку");
    ui->idLineEdit->setText(QString::number(id));

    ui->addEntryButton->setDisabled(true);
}

NewTouristPackageEntryDialog::NewTouristPackageEntryDialog(TouristPackageEntry *touristPackageEntry, DataStorage *dataStorage, QWidget *parent)
    : QDialog(parent)
      , ui(new Ui::NewTouristPackageEntryDialog)
      , m_dataStorage(dataStorage)
      , m_touristPackageEntry(touristPackageEntry){
    ui->setupUi(this);

    isNew = false;

    this->setWindowTitle("Изменить путевку");
    
    ui->idLineEdit->setText(QString::number(m_touristPackageEntry->m_id.value()));

    m_touristsIds = m_touristPackageEntry->m_touristsIds;
    QString labelText = "ID выбранных туристов: ";
    bool isFirst = true;
    for (auto id: m_touristsIds) {
        if (isFirst) {
            labelText += QString::number(id);
            isFirst = false;
        }
        else {
            labelText += ", " + QString::number(id);
        }
    }
    ui->chosenTouristsLabel->setText(labelText);

    m_destinationId = touristPackageEntry->m_destinationId;
    ui->chooseDestinationButton->setText("ID выбранного направления: " + QString::number(m_destinationId.value()));

    ui->arrivalDateDateEdit->setDate(m_touristPackageEntry->m_arrivalDate);
    ui->durationSpinBox->setValue(m_touristPackageEntry->m_duration);
    ui->finalPriceDoubleSpinBox->setValue(m_touristPackageEntry->m_finalPrice);

    ui->addEntryButton->setText("Изменить запись");
    ui->addEntryButton->setEnabled(true);
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

        QString labelText = "ID выбранных туристов: ";
        bool isFirst = true;

        for (auto id: m_touristsIds) {
            if (isFirst) {
                labelText += QString::number(id);
                isFirst = false;
            }
            else {
                labelText += ", " + QString::number(id);
            }
        }
        ui->chosenTouristsLabel->setText(labelText);
    }

    checkIfAcceptable();
}


void NewTouristPackageEntryDialog::on_chooseDestinationButton_clicked() {
    DestinationTableModel tableModel(m_dataStorage, this);

    EntrySelectionDialog entry_selection_dialog(true, &tableModel);

    if (entry_selection_dialog.exec()) {
        m_destinationId = entry_selection_dialog.getChosenIndex();

        ui->chooseDestinationButton->setText("ID выбранного направления: " + QString::number(m_destinationId.value()));
    }

    checkIfAcceptable();
}

void NewTouristPackageEntryDialog::checkIfAcceptable() {
    if (!m_touristsIds.isEmpty() && m_destinationId.has_value()) {
        ui->addEntryButton->setEnabled(true);
    }
}

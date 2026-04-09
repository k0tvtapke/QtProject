#ifndef NEWTOURISTPACKAGEENTRYDIALOG_H
#define NEWTOURISTPACKAGEENTRYDIALOG_H

#include "datastorage.h"

#include <QDialog>

namespace Ui {
    class NewTouristPackageEntryDialog;
}

class NewTouristPackageEntryDialog : public QDialog {
    Q_OBJECT

public:
    explicit NewTouristPackageEntryDialog(size_t id, DataStorage *dataStorage, QWidget *parent = nullptr);

    explicit NewTouristPackageEntryDialog(TouristPackageEntry *touristPackageEntry, DataStorage *dataStorage, QWidget *parent = nullptr);

    ~NewTouristPackageEntryDialog();

    TouristPackageEntry getTouristPackageEntry() const;

private slots:
    void on_addEntryButton_clicked();

    void on_cancelButton_clicked();

    void on_chooseTouristButton_clicked();

    void on_chooseDestinationButton_clicked();

private:
    bool isNew;
    DataStorage *m_dataStorage;

    QList<uint32_t> m_touristsIds;
    std::optional<uint32_t> m_destinationId;
    TouristPackageEntry *m_touristPackageEntry;

    Ui::NewTouristPackageEntryDialog *ui;

    void checkIfAcceptable();
};

#endif // NEWTOURISTPACKAGEENTRYDIALOG_H

#ifndef NEWDESTINATIONENTRYDIALOG_H
#define NEWDESTINATIONENTRYDIALOG_H

#include "datastorage.h"

#include <QDialog>

namespace Ui {
    class NewDestinationEntryDialog;
}

class NewDestinationEntryDialog : public QDialog {
    Q_OBJECT

public:
    explicit NewDestinationEntryDialog(size_t id, QWidget *parent = nullptr);

    explicit NewDestinationEntryDialog(DestinationEntry *destinationEntry, QWidget *parent = nullptr);

    ~NewDestinationEntryDialog();

    DestinationEntry getDestinationEntry() const;

private slots:
    void on_addEntryButton_clicked();

    void on_cancelButton_clicked();

private:
    bool isNew;
    DestinationEntry *m_destination_entry;

    Ui::NewDestinationEntryDialog *ui;
};

#endif // NEWDESTINATIONENTRYDIALOG_H

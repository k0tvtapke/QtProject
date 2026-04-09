#ifndef NEWTOURISTENTRYDIALOG_H
#define NEWTOURISTENTRYDIALOG_H

#include "datastorage.h"

#include <QDialog>

namespace Ui {
    class NewTouristEntryDialog;
}

class NewTouristEntryDialog : public QDialog {
    Q_OBJECT

public:
    explicit NewTouristEntryDialog(size_t id, QWidget *parent = nullptr);

    explicit NewTouristEntryDialog(TouristEntry *touristEntry, QWidget *parent = nullptr);

    ~NewTouristEntryDialog();

    TouristEntry getTouristEntry() const;

private slots:
    void on_addEntryButton_clicked();

    void on_cancelButton_clicked();

private:
    bool isNew;
    TouristEntry *m_touristEntry;

    Ui::NewTouristEntryDialog *ui;
};

#endif // NEWTOURISTENTRYDIALOG_H

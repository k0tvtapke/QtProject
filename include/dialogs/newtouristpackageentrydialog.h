#ifndef NEWTOURISTPACKAGEENTRYDIALOG_H
#define NEWTOURISTPACKAGEENTRYDIALOG_H

#include <QDialog>

namespace Ui {
class NewTouristPackageEntryDialog;
}

class NewTouristPackageEntryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTouristPackageEntryDialog(QWidget *parent = nullptr);
    ~NewTouristPackageEntryDialog();

private:
    Ui::NewTouristPackageEntryDialog *ui;
};

#endif // NEWTOURISTPACKAGEENTRYDIALOG_H

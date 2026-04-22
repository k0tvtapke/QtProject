#ifndef REPORTDIALOG_H
#define REPORTDIALOG_H

#include <QDialog>

namespace Ui {
class ReportDialog;
}

class ReportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReportDialog(QWidget *parent, QString &text);
    ~ReportDialog();

private slots:
    void on_copyButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::ReportDialog *ui;
};

#endif // REPORTDIALOG_H

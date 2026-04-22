#include "dialogs/reportdialog.h"
#include "ui_reportdialog.h"

#include <QClipboard>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

ReportDialog::ReportDialog(QWidget* parent, QString& text)
    : QDialog(parent)
      , ui(new Ui::ReportDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Отчет");

    ui->reportTextEdit->setText(text);
}

ReportDialog::~ReportDialog()
{
    delete ui;
}

void ReportDialog::on_copyButton_clicked()
{
    QString text = ui->reportTextEdit->toPlainText();
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(text);
}


void ReportDialog::on_saveButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Выберите, куда сохранить отчет",
                                                    QDir::homePath(),
                                                    "*.txt;;*");

    if (!filePath.isEmpty())
    {
        QFile file(filePath);

        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);

            out << ui->reportTextEdit->toPlainText();

            file.close();

            QMessageBox::information(this, "Успешное сохранение файла", "Файл был успешно сохранен");
        }
        else
        {
            QMessageBox::critical(this, "Ошибка сохранения отчета", "Не удалось сохранить отчет в файл!");
        }
    }
}

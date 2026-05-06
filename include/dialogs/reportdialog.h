#ifndef REPORTDIALOG_H
#define REPORTDIALOG_H

#include <QDialog>

namespace Ui {
    class ReportDialog;
}

/**
 * @class ReportDialog
 * @brief Диалог просмотра текстового отчёта.
 * @details Поддерживает копирование текста в буфер и сохранение в `.txt`-файл.
 *
 * @extends QDialog
 */
class ReportDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Конструктор.
     * @param parent Родительский виджет.
     * @param text Текст отчёта (передаётся по ссылке).
     */
    explicit ReportDialog(QWidget *parent, QString &text);

    /**
     * @override QDialog::~QDialog
     */
    ~ReportDialog();

private slots:
    /**
     * @brief Скопировать содержимое отчёта в буфер обмена.
     */
    void on_copyButton_clicked();

    /**
     * @brief Сохранить содержимое отчёта в текстовый файл.
     */
    void on_saveButton_clicked();

private:
    Ui::ReportDialog *ui;       ///< Сгенерированный uic-объект.
};

#endif // REPORTDIALOG_H

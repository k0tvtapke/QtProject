#ifndef BASECHARTDIALOG_H
#define BASECHARTDIALOG_H

#include <QDialog>
#include <QtCharts>

QT_CHARTS_USE_NAMESPACE

/**
 * @class BaseChartDialog
 * @brief Базовый класс диалогов с QtCharts-визуализацией.
 * @details Содержит общую обвязку: заголовок окна, флаги Maximize/Minimize,
 *          размер по умолчанию и установка `QChart` через `installChart()`.
 *
 * @extends QDialog
 */
class BaseChartDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Конструктор.
     * @param title Заголовок окна.
     * @param size Стартовый размер.
     * @param parent Родительский виджет.
     */
    explicit BaseChartDialog(const QString &title, const QSize &size, QWidget *parent = nullptr);

    /**
     * @override QDialog::~QDialog
     */
    ~BaseChartDialog() override = default;

protected:
    /**
     * @brief Установить переданный QChart в QChartView и в layout диалога.
     * @param chart Указатель на QChart (BaseChartDialog не управляет владением напрямую,
     *              но layout/Qt-родительство позаботятся о удалении вместе с диалогом).
     */
    void installChart(QChart *chart);
};

#endif // BASECHARTDIALOG_H

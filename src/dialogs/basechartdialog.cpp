#include "dialogs/basechartdialog.h"

#include <QVBoxLayout>
#include <QtCharts/QChartView>

BaseChartDialog::BaseChartDialog(const QString &title, const QSize &size, QWidget *parent)
    : QDialog(parent) {
    setWindowTitle(title);
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
    resize(size);
}

void BaseChartDialog::installChart(QChart *chart) {
    auto *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    if (layout()) delete layout();
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(chartView);
    setLayout(mainLayout);
}

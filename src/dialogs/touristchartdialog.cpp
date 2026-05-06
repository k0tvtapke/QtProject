#include "dialogs/touristchartdialog.h"

TouristChartDialog::TouristChartDialog(DataStorage *storage, QWidget *parent)
    : BaseChartDialog(tr("Распределение туристов по полу"), QSize(700, 600), parent) {
    setupChart(storage);
}

void TouristChartDialog::setupChart(DataStorage *storage) {
    if (!storage) return;

    int maleCount = 0;
    int femaleCount = 0;

    for (const auto &tourist : storage->m_touristEntries) {
        if (!tourist.m_isRemoved) {
            if (tourist.m_gender == Gender::MALE) maleCount++;
            else femaleCount++;
        }
    }

    auto *series = new QPieSeries();

    if (maleCount > 0) {
        auto *slice = series->append(tr("Мужчины (%1)").arg(maleCount), maleCount);
        slice->setBrush(QColor(100, 150, 255));
    }
    if (femaleCount > 0) {
        auto *slice = series->append(tr("Женщины (%1)").arg(femaleCount), femaleCount);
        slice->setBrush(QColor(255, 150, 150));
    }

    for (auto *slice : series->slices()) {
        connect(slice, &QPieSlice::hovered, [slice](bool hovered) {
            slice->setExploded(hovered);
            slice->setLabelVisible(hovered);
        });
    }

    auto *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(tr("Соотношение полов туристов"));
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setAlignment(Qt::AlignBottom);

    installChart(chart);
}

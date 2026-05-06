#include "dialogs/destinationchartdialog.h"

#include <QMap>

DestinationChartDialog::DestinationChartDialog(DataStorage *storage, QWidget *parent)
    : BaseChartDialog(tr("Распределение отелей по звездам"), QSize(700, 600), parent) {
    setupChart(storage);
}

void DestinationChartDialog::setupChart(DataStorage *storage) {
    if (!storage) return;

    QMap<int, int> starsCount;
    for (const auto &dest : storage->m_destinationEntries) {
        if (!dest.m_isRemoved && dest.m_hotelStars >= 1 && dest.m_hotelStars <= 5) {
            starsCount[dest.m_hotelStars]++;
        }
    }

    auto *series = new QPieSeries();

    for (int stars = 1; stars <= 5; ++stars) {
        const int count = starsCount.value(stars, 0);
        if (count > 0) {
            QString label = QString(tr("%1 ★ (%2)")).arg(stars).arg(count);
            QPieSlice *slice = series->append(label, count);

            slice->setLabelVisible(false);

            connect(slice, &QPieSlice::hovered, [slice](bool hovered) {
                slice->setExploded(hovered);
                slice->setLabelVisible(hovered);
            });
        }
    }

    auto *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(tr("Рейтинг отелей по количеству звезд"));
    chart->setAnimationOptions(QChart::AllAnimations);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setFont(QFont("Arial", 10));

    installChart(chart);
}

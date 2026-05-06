#include "dialogs/touristpackagechartdialog.h"

#include <QMap>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <algorithm>

TouristPackageChartDialog::TouristPackageChartDialog(DataStorage *storage, QWidget *parent)
    : BaseChartDialog(tr("Рейтинг популярности направлений"), QSize(1000, 700), parent) {
    setupChart(storage);
}

void TouristPackageChartDialog::setupChart(DataStorage *storage) {
    if (!storage) return;

    QMap<quint32, QString> idToName;
    for (const auto &dest : storage->m_destinationEntries) {
        if (!dest.m_isRemoved && dest.m_id.has_value()) {
            idToName[dest.m_id.value()] = QString("%1, %2").arg(dest.m_country, dest.m_city);
        }
    }

    QMap<QString, int> aggregatedStats;
    for (const auto &package : storage->m_touristPackageEntries) {
        if (!package.m_isRemoved) {
            QString name = idToName.value(package.m_destinationId, tr("Неизвестно"));
            aggregatedStats[name]++;
        }
    }

    QList<QPair<QString, int>> statsList;
    for (auto it = aggregatedStats.begin(); it != aggregatedStats.end(); ++it) {
        statsList.append({it.key(), it.value()});
    }

    std::sort(statsList.begin(), statsList.end(), [](const QPair<QString, int> &a, const QPair<QString, int> &b) {
        return a.second > b.second;
    });

    if (statsList.size() > 10) {
        statsList = statsList.mid(0, 10);
    }

    std::reverse(statsList.begin(), statsList.end());

    auto *series = new QHorizontalBarSeries();
    auto *set = new QBarSet(tr("Продано туров"));
    QStringList categories;
    int maxCount = 0;

    for (const auto &pair : statsList) {
        *set << pair.second;
        categories << pair.first;
        if (pair.second > maxCount) maxCount = pair.second;
    }
    series->append(set);

    auto *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(tr("ТОП-10 самых популярных направлений"));

    auto *axisY = new QBarCategoryAxis();
    axisY->append(categories);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    auto setupXAxis = [&](QValueAxis *axis) {
        axis->setLabelFormat("%d");
        const int range = (maxCount < 1) ? 1 : maxCount;
        axis->setRange(0, range);
        axis->setTickCount(range + 1);
        axis->setMinorTickCount(0);
    };

    auto *axisXBottom = new QValueAxis();
    setupXAxis(axisXBottom);
    chart->addAxis(axisXBottom, Qt::AlignBottom);
    series->attachAxis(axisXBottom);

    auto *axisXTop = new QValueAxis();
    setupXAxis(axisXTop);
    chart->addAxis(axisXTop, Qt::AlignTop);
    series->attachAxis(axisXTop);

    installChart(chart);
}

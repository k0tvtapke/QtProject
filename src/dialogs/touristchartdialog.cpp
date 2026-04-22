#include "dialogs/touristchartdialog.h"
#include <QVBoxLayout>

TouristChartDialog::TouristChartDialog(DataStorage* storage, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Распределение туристов по полу"));
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);
    resize(700, 600);

    setupChart(storage);
}

TouristChartDialog::~TouristChartDialog()
{
}

void TouristChartDialog::setupChart(DataStorage* storage)
{
    if (!storage) return;

    int maleCount = 0;
    int femaleCount = 0;

    for (const auto& tourist : storage->m_touristEntries)
    {
        if (!tourist.m_isRemoved)
        {
            if (tourist.m_gender == Gender::MALE) maleCount++;
            else femaleCount++;
        }
    }

    QPieSeries* series = new QPieSeries();

    if (maleCount > 0)
    {
        auto* slice = series->append(tr("Мужчины (%1)").arg(maleCount), maleCount);
        slice->setBrush(QColor(100, 150, 255)); // Голубой
    }
    if (femaleCount > 0)
    {
        auto* slice = series->append(tr("Женщины (%1)").arg(femaleCount), femaleCount);
        slice->setBrush(QColor(255, 150, 150)); // Розовый
    }

    // Интерактивность при наведении
    for (auto* slice : series->slices())
    {
        connect(slice, &QPieSlice::hovered, [slice](bool hovered)
        {
            slice->setExploded(hovered);
            slice->setLabelVisible(hovered);
        });
    }

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(tr("Соотношение полов туристов"));
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    if (layout()) delete layout();
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(chartView);
    setLayout(mainLayout);
}

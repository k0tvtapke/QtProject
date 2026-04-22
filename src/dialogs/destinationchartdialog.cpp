#include "dialogs/destinationchartdialog.h"
#include <QVBoxLayout>
#include <QMap>

DestinationChartDialog::DestinationChartDialog(DataStorage* storage, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Распределение отелей по звездам"));
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);
    resize(700, 600);

    setupChart(storage);
}

DestinationChartDialog::~DestinationChartDialog()
{
}

void DestinationChartDialog::setupChart(DataStorage* storage)
{
    if (!storage) return;

    // 1. Подсчет статистики
    QMap<int, int> starsCount;
    for (const auto& dest : storage->m_destinationEntries)
    {
        if (!dest.m_isRemoved && dest.m_hotelStars >= 1 && dest.m_hotelStars <= 5)
        {
            starsCount[dest.m_hotelStars]++;
        }
    }

    // 2. Создание серии
    QPieSeries* series = new QPieSeries();

    for (int stars = 1; stars <= 5; ++stars)
    {
        int count = starsCount.value(stars, 0);
        if (count > 0)
        {
            // Формируем текст для легенды
            QString label = QString(tr("%1 ★ (%2)")).arg(stars).arg(count);
            QPieSlice* slice = series->append(label, count);

            // УБИРАЕМ подписи с самой диаграммы, чтобы не было наслоения
            slice->setLabelVisible(false);

            // Добавим интерактивности: при наведении сектор будет чуть "выпрыгивать"
            connect(slice, &QPieSlice::hovered, [slice](bool hovered)
            {
                slice->setExploded(hovered);
                slice->setLabelVisible(hovered); // Показать подпись ТОЛЬКО при наведении
            });
        }
    }

    // 3. Создание чарта
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(tr("Рейтинг отелей по количеству звезд"));
    chart->setAnimationOptions(QChart::AllAnimations);

    // 4. Настройка легенды
    // Теперь легенда — наш основной источник информации
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setFont(QFont("Arial", 10));

    // 5. Вывод
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Очистка старого лейаута, если он был
    if (layout()) delete layout();
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);
}

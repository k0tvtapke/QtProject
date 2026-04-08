#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

void createDataStorageEntries(DataStorage *dataStorage) {
    // --- НАПРАВЛЕНИЯ (Destinations) ---
    // ID будут присвоены автоматически при добавлении, если твоя логика addDestinationEntry это делает.
    // Если нет, то в TouristPackageEntry нужно будет указывать индексы или реальные ID после добавления.

    dataStorage->addDestinationEntry(DestinationEntry("Turkey", "Antalya", 850.0, FoodType::AI, 5));
    dataStorage->addDestinationEntry(DestinationEntry("Turkey", "Kemer", 720.0, FoodType::AI, 4));
    dataStorage->addDestinationEntry(DestinationEntry("Egypt", "Sharm el-Sheikh", 900.0, FoodType::UAI, 5));
    dataStorage->addDestinationEntry(DestinationEntry("Egypt", "Hurghada", 650.0, FoodType::HB, 4));
    dataStorage->addDestinationEntry(DestinationEntry("Thailand", "Phuket", 1200.0, FoodType::BB, 4));
    dataStorage->addDestinationEntry(DestinationEntry("Thailand", "Pattaya", 950.0, FoodType::RO, 3));
    dataStorage->addDestinationEntry(DestinationEntry("UAE", "Dubai", 1500.0, FoodType::BB, 5));
    dataStorage->addDestinationEntry(DestinationEntry("UAE", "Abu Dhabi", 1350.0, FoodType::HB, 5));
    dataStorage->addDestinationEntry(DestinationEntry("Russia", "Sochi", 450.0, FoodType::FB, 4));
    dataStorage->addDestinationEntry(DestinationEntry("Russia", "Anapa", 300.0, FoodType::RO, 3));
    dataStorage->addDestinationEntry(DestinationEntry("Maldives", "Male", 2500.0, FoodType::UAI, 5));
    dataStorage->addDestinationEntry(DestinationEntry("Sri Lanka", "Colombo", 1100.0, FoodType::HB, 4));
    dataStorage->addDestinationEntry(DestinationEntry("Cuba", "Havana", 1400.0, FoodType::AI, 4));
    dataStorage->addDestinationEntry(DestinationEntry("Dominican Republic", "Punta Cana", 1600.0, FoodType::AI, 5));
    dataStorage->addDestinationEntry(DestinationEntry("Vietnam", "Nha Trang", 980.0, FoodType::BB, 4));

    // --- ТУРИСТЫ (Tourists) ---
    // Генерируем разнообразных людей

    // Мужчины
    dataStorage->addTouristEntry(TouristEntry("Ivan", "Ivanov", Gender::MALE, QDate(1980, 5, 12)));
    dataStorage->addTouristEntry(TouristEntry("Petr", "Petrov", Gender::MALE, QDate(1975, 11, 23)));
    dataStorage->addTouristEntry(TouristEntry("Sergey", "Sidorov", "Alexandrovich", Gender::MALE, QDate(1990, 1, 30)));
    dataStorage->addTouristEntry(TouristEntry("Dmitry", "Kuznetsov", Gender::MALE, QDate(1985, 7, 15)));
    dataStorage->addTouristEntry(TouristEntry("Alexey", "Smirnov", Gender::MALE, QDate(1995, 3, 5)));
    dataStorage->addTouristEntry(TouristEntry("Maxim", "Volkov", "Igorevich", Gender::MALE, QDate(1988, 9, 10)));
    dataStorage->addTouristEntry(TouristEntry("Andrey", "Popov", Gender::MALE, QDate(1970, 12, 25)));
    dataStorage->addTouristEntry(TouristEntry("Nikolay", "Sokolov", Gender::MALE, QDate(2000, 6, 1)));
    dataStorage->addTouristEntry(TouristEntry("Vladimir", "Lebedev", Gender::MALE, QDate(1982, 4, 18)));
    dataStorage->addTouristEntry(TouristEntry("Oleg", "Novikov", Gender::MALE, QDate(1992, 8, 22)));

    // Женщины
    dataStorage->addTouristEntry(TouristEntry("Elena", "Ivanova", Gender::FEMALE, QDate(1982, 6, 14)));
    dataStorage->addTouristEntry(TouristEntry("Maria", "Petrova", "Sergeevna", Gender::FEMALE, QDate(1978, 3, 8)));
    dataStorage->addTouristEntry(TouristEntry("Anna", "Sidorova", Gender::FEMALE, QDate(1991, 11, 11)));
    dataStorage->addTouristEntry(TouristEntry("Olga", "Kuznetsova", Gender::FEMALE, QDate(1986, 2, 20)));
    dataStorage->addTouristEntry(TouristEntry("Tatiana", "Smirnova", "Dmitrievna", Gender::FEMALE, QDate(1994, 7, 7)));
    dataStorage->addTouristEntry(TouristEntry("Natalia", "Volkova", Gender::FEMALE, QDate(1989, 12, 30)));
    dataStorage->addTouristEntry(TouristEntry("Ekaterina", "Popova", Gender::FEMALE, QDate(1972, 5, 16)));
    dataStorage->addTouristEntry(TouristEntry("Svetlana", "Sokolova", Gender::FEMALE, QDate(2001, 9, 9)));
    dataStorage->addTouristEntry(TouristEntry("Irina", "Lebedeva", "Andreevna", Gender::FEMALE, QDate(1983, 1, 25)));
    dataStorage->addTouristEntry(TouristEntry("Yulia", "Novikova", Gender::FEMALE, QDate(1996, 4, 12)));

    // 1. Семья Ивановых (Папа, Мама, Ребенок) в Анталию
    dataStorage->addTouristPackageEntry(TouristPackageEntry(
        {1, 2, 3}, // Ivan, Elena, Artem
        1, // Antalya
        QDate(2026, 6, 1),
        14,
        2500.0
    ));

    // 2. Пара Петровых (без детей) в Шарм-эль-Шейх
    dataStorage->addTouristPackageEntry(TouristPackageEntry(
        {4, 5}, // Petr, Maria
        3, // Sharm el-Sheikh
        QDate(2026, 7, 10),
        10,
        1900.0
    ));

    // 3. Молодой человек (Сидоров) в Паттайю (бюджетно)
    dataStorage->addTouristPackageEntry(TouristPackageEntry(
        {6}, // Sergey Sidorov
        6, // Pattaya
        QDate(2026, 11, 5),
        21,
        900.0
    ));

    // 4. Друзья (Кузнецов и Смирнова) в Дубай
    dataStorage->addTouristPackageEntry(TouristPackageEntry(
        {7, 8}, // Dmitry Kuznetsov, Olga Kuznetsova (предположим, однофамильцы или друзья)
        7, // Dubai
        QDate(2026, 12, 20),
        7,
        3200.0
    ));

    // 5. Одиночный турист (Волков) в Сочи
    dataStorage->addTouristPackageEntry(TouristPackageEntry(
        {9}, // Maxim Volkov
        9, // Sochi
        QDate(2026, 8, 15),
        14,
        600.0
    ));

    // 6. Большая компания в Доминикану
    dataStorage->addTouristPackageEntry(TouristPackageEntry(
        {10, 11, 12, 13}, // Alexey Smirnov, Tatiana Smirnova, Natalia Volkova, Ekaterina Popova
        14, // Punta Cana
        QDate(2027, 1, 10),
        12,
        6500.0
    ));

    // 7. Романтическая поездка (Новиков и Лебедева) на Мальдивы
    dataStorage->addTouristPackageEntry(TouristPackageEntry(
        {14, 15}, // Oleg Novikov, Irina Lebedeva
        11, // Maldives
        QDate(2026, 9, 1),
        10,
        5500.0
    ));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
      , m_dataStorage(new DataStorage) {
    ui->setupUi(this);

    this->setWindowTitle("АРМ Сотрудника");

    // createDataStorageEntries(m_dataStorage);

    PrepareDestinationTab();
    PrepareTouristTab();
    PrepareTouristPackageTab();
}

MainWindow::~MainWindow() {
    delete ui;
    delete m_dataStorage;
}

void MainWindow::PrepareDestinationTab() {
    m_destinationTabWidget = new DestinationTabWidget(m_dataStorage, this);

    ui->tabWidget->addTab(m_destinationTabWidget, "Направления");
}

void MainWindow::PrepareTouristTab() {
    m_touristTabWidget = new TouristTabWidget(m_dataStorage, this);

    ui->tabWidget->addTab(m_touristTabWidget, "Туристы");
}

void MainWindow::PrepareTouristPackageTab() {
    m_touristPackageTabWidget = new TouristPackageTabWidget(m_dataStorage, this);

    ui->tabWidget->addTab(m_touristPackageTabWidget, "Путёвки");
}

void MainWindow::on_loadDatabaseButton_clicked() {
    const QString filePath = QFileDialog::getOpenFileName(this, "Выберите, куда сохранить базу данных",
                                                          m_chosenFilePath.isEmpty()
                                                              ? QDir::homePath()
                                                              : m_chosenFilePath,
                                                          "*.bin");

    if (!filePath.isEmpty()) {
        m_chosenFilePath = filePath;

        if (m_dataStorage->loadFromFile(filePath)) {
            ui->chosenFileLabel->setText("Выбранный файл базы данных: " + filePath);

            m_destinationTabWidget->reloadTable();
            m_touristTabWidget->reloadTable();
            m_touristPackageTabWidget->reloadTable();

            m_destinationTabWidget->resizeTable();
            m_touristTabWidget->resizeTable();
            m_touristPackageTabWidget->resizeTable();
        } else {
            QMessageBox::critical(this, "Ошибка чтения файла", "Не удалось загрузить файл");
        }
    }
}


void MainWindow::on_saveDatabaseButton_clicked() {
    const QString filePath = QFileDialog::getSaveFileName(this, "Выберите, куда сохранить базу данных",
                                                          m_chosenFilePath.isEmpty()
                                                              ? QDir::homePath()
                                                              : m_chosenFilePath,
                                                          "*.bin");

    if (!filePath.isEmpty()) {
        m_chosenFilePath = filePath;
        ui->chosenFileLabel->setText("Выбранный файл базы данных: " + filePath);

        if (m_dataStorage->saveToFile(m_chosenFilePath)) {
            QMessageBox::information(this, "Сохранение файла", "Файл был успешно сохранен");
        }
        else {
            QMessageBox::critical(this, "Ошибка записи файла", "Не удалось сохранить файл");
        }
    }
}

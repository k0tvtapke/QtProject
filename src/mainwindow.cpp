#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
      , m_dataStorage(new DataStorage) {
    ui->setupUi(this);

    this->setWindowTitle("АРМ Сотрудника");

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

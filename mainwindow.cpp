#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "databasetabwidget.h"

#include <QVBoxLayout>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->setWindowTitle("АРМ Сотрудника");

    PrepareDestinationTab();
    PrepareTouristsTab();
    PrepareTouristPackagesTab();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setTabWidget(QWidget *widget, QWidget *tabWidget) {
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(widget);
    // tabWidget->setContentsMargins(0, 0, 0, 0);
    // layout->setContentsMargins(0, 0, 0, 0);

    tabWidget->setLayout(layout);
}

void MainWindow::PrepareDestinationTab() {
    m_destinationTabWidget = new DatabaseTabWidget;
    setTabWidget(m_destinationTabWidget, ui->destinationsTab);
}

void MainWindow::PrepareTouristsTab() {
    m_touristsTabWidget = new DatabaseTabWidget;
    setTabWidget(m_touristsTabWidget, ui->touristsTab);
}

void MainWindow::PrepareTouristPackagesTab() {
    m_touristPackagesTabWidget = new DatabaseTabWidget;
    setTabWidget(m_touristPackagesTabWidget, ui->touristPackagesTab);
}

void MainWindow::on_loadDatabaseButton_clicked() {
    QString filePath;

    if (m_chosenFilePath.isEmpty()) {
        filePath = QFileDialog::getOpenFileName(this, "Выберите, куда сохранить базу данных", QDir::homePath(),
                                                "*.bin");
    } else {
        filePath = QFileDialog::getOpenFileName(this, "Выберите, куда сохранить базу данных", m_chosenFilePath,
                                                "*.bin");
    }

    if (!filePath.isEmpty()) {
        m_chosenFilePath = filePath;
        ui->chosenFileLabel->setText("Выбранный файл базы данных: " + filePath);
    }
}


void MainWindow::on_saveDatabaseButton_clicked() {
    QString filePath;

    if (m_chosenFilePath.isEmpty()) {
        filePath = QFileDialog::getSaveFileName(this, "Выберите, куда сохранить базу данных", QDir::homePath(),
                                                "*.bin");
    } else {
        filePath = QFileDialog::getSaveFileName(this, "Выберите, куда сохранить базу данных", m_chosenFilePath,
                                                "*.bin");
    }

    if (!filePath.isEmpty()) {
        if (m_chosenFilePath.isEmpty()) {
            m_chosenFilePath = filePath;
            ui->chosenFileLabel->setText("Выбранный файл базы данных: " + filePath);
        }

        QMessageBox::information(this, "Сохранение файла", "Файл был успешно сохранен");
    }
}

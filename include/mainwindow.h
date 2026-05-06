#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "datastorage.h"
#include "widgets/destinationtabwidget.h"
#include "widgets/touristpackagetabwidget.h"
#include "widgets/touristtabwidget.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Главное окно приложения.
 * @details Содержит вкладки `DestinationTabWidget`, `TouristTabWidget`,
 *          `TouristPackageTabWidget`, а также кнопки загрузки/сохранения БД.
 *
 * @extends QMainWindow
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Конструктор. Создаёт `DataStorage`, инициализирует вкладки.
     * @param parent Родительский виджет (обычно nullptr).
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Деструктор. Освобождает UI и хранилище.
     * @override QMainWindow::~QMainWindow
     */
    ~MainWindow() override;

private slots:
    /**
     * @brief Открывает диалог выбора файла БД и загружает данные.
     * @details При успехе обновляет ярлык пути и перезагружает все вкладки.
     */
    void on_loadDatabaseButton_clicked();

    /**
     * @brief Открывает диалог выбора файла и сохраняет БД.
     */
    void on_saveDatabaseButton_clicked();

private:
    Ui::MainWindow *ui;             ///< Сгенерированный uic-объект.
    DataStorage *m_dataStorage;     ///< In-memory БД.

    /**
     * @brief Создаёт вкладку направлений.
     */
    void PrepareDestinationTab();

    /**
     * @brief Создаёт вкладку туристов.
     */
    void PrepareTouristTab();

    /**
     * @brief Создаёт вкладку путёвок.
     */
    void PrepareTouristPackageTab();

    QString m_chosenFilePath = "";  ///< Последний выбранный путь к файлу БД.

    DestinationTabWidget *m_destinationTabWidget;       ///< Вкладка «Направления».
    TouristTabWidget *m_touristTabWidget;               ///< Вкладка «Туристы».
    TouristPackageTabWidget *m_touristPackageTabWidget; ///< Вкладка «Путёвки».
};
#endif // MAINWINDOW_H

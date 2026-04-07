#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "datastorage.h"
#include "widgets/destinationtabwidget.h"
#include "widgets/touristtabwidget.h"
#include "widgets/touristpackagetabwidget.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:
    void on_loadDatabaseButton_clicked();

    void on_saveDatabaseButton_clicked();

private:
    Ui::MainWindow *ui;

    DataStorage *m_dataStorage;

    void PrepareDestinationTab();

    void PrepareTouristTab();

    void PrepareTouristPackageTab();

    // void PrepareTouristPackagesTab();

    QString m_chosenFilePath = "";

    DestinationTabWidget *m_destinationTabWidget;
    TouristTabWidget *m_touristTabWidget;
    TouristPackageTabWidget *m_touristPackageTabWidget;
};
#endif // MAINWINDOW_H

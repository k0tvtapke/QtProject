#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "databasetabwidget.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_loadDatabaseButton_clicked();

    void on_saveDatabaseButton_clicked();

private:
    Ui::MainWindow *ui;

    void setTabWidget(QWidget *widget, QWidget *tabWidget);

    void PrepareDestinationTab();
    void PrepareTouristsTab();
    void PrepareTouristPackagesTab();

    QString m_chosenFilePath = "";

    DatabaseTabWidget *m_destinationTabWidget;
    DatabaseTabWidget *m_touristsTabWidget;
    DatabaseTabWidget *m_touristPackagesTabWidget;
};
#endif // MAINWINDOW_H

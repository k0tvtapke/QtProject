#ifndef DATABASETABWIDGET_H
#define DATABASETABWIDGET_H

#include <QWidget>

namespace Ui {
class DatabaseTabWidget;
}

class DatabaseTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseTabWidget(QWidget *parent = nullptr);
    ~DatabaseTabWidget();

private:
    Ui::DatabaseTabWidget *ui;
};

#endif // DATABASETABWIDGET_H

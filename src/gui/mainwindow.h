#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include <ui_mainwindow.h>

class SqlEngine;
class ScheduleXmlParser;

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void importSchedule();
    void showParsingProgress(int aStatus);
    void aboutApp();
    void updateDayView(const QDate &aDate);
    void updateTab(const int n);
    void updateActivitiesDayView(const QDate &aDate);
    void updateFavouritesDayView(const QDate &aDate);
    void itemClicked(const QModelIndex &aIndex);
    void displayMap(const QModelIndex &aIndex);
    void searchClicked();
private:
    SqlEngine *mSqlEngine;
    ScheduleXmlParser *mXmlParser;
};

#endif // MAINWINDOW_H


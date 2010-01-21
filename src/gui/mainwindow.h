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
    // aEventId is used to inform widget to automatically open
    // Event dialog for given Event ID
    MainWindow(int aEventId = 0, QWidget *aParent = NULL);
    ~MainWindow();
private slots:
    void importSchedule();
    void showParsingProgress(int aStatus);
    void aboutApp();
    void updateDayView(const QDate &aDate);
    void updateTab(const int n);
    void updateTracksView(const QDate &aDate);
    void updateFavouritesView(const QDate &aDate);
    void updateSearchView(const QDate &aDate);
    void itemClicked(const QModelIndex &aIndex);
    void displayMap(const QModelIndex &aIndex);
    void searchClicked();
private:
    SqlEngine *mSqlEngine;
    ScheduleXmlParser *mXmlParser;
};

#endif // MAINWINDOW_H


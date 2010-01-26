#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include <ui_mainwindow.h>

class SqlEngine;

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
    void aboutApp();
    void updateDayView(const QDate &aDate);
    void updateTracksView(const QDate &aDate);
    void updateFavouritesView(const QDate &aDate);
    void updateSearchView(const QDate &aDate);
    void updateNowView();
    void updateRoomView(const QDate &aDate);
    void itemClicked(const QModelIndex &aIndex);
    void displayMap(const QModelIndex &aIndex);
    void displayWarning(const QModelIndex &aIndex);
    void searchClicked();
	void searchAgainClicked();
    void conferenceMapClicked();
    void tabHasChanged(int aIndex);
    void eventHasChanged(int aEventId);
    void timerUpdateNowView();
private:
    SqlEngine *mSqlEngine;
};

#endif // MAINWINDOW_H


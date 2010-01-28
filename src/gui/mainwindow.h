#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include <ui_mainwindow.h>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT
public:
    // aEventId is used to inform widget to automatically open
    // Event dialog for given Event ID
    MainWindow(int aEventId = 0, QWidget *aParent = NULL);
    ~MainWindow() {}
private slots:
    void scheduleImported(int aConfId);
    void aboutApp();
    void conferenceMapClicked();
    void eventHasChanged(int aEventId, bool aReloadModel);
private:
    void fillAndShowConferenceHeader();
    void initTabs();
};

#endif /* MAINWINDOW_H */


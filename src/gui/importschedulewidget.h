#ifndef IMPORTSCHEDULEWIDGET_H
#define IMPORTSCHEDULEWIDGET_H

#include <QWidget>
#include "ui_importschedulewidget.h"

class ScheduleXmlParser;
class SqlEngine;

class ImportScheduleWidget : public QWidget, Ui::ImportScheduleWidget
{
    Q_OBJECT
    public:
        ImportScheduleWidget(QWidget *aParent = NULL); // don't forget to use setSqlEngine()
        ~ImportScheduleWidget();
        void setSqlEngine(SqlEngine *aSqlEngine);
    private slots:
        void browseSchedule();
        void parsingSchedule(const QString &aTitle);
        void showParsingProgress(int progress);
    signals:
        void scheduleImported(int confId);
    private:
        ScheduleXmlParser *mXmlParser;
        SqlEngine *mSqlEngine; // uses it
};

#endif /* IMPORTSCHEDULEWIDGET_H */


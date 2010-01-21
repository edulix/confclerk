#ifndef IMPORTSCHEDULEDIALOG_H
#define IMPORTSCHEDULEDIALOG_H

#include <QDialog>
#include "ui_importscheduledialog.h"

class ScheduleXmlParser;
class SqlEngine;

class ImportScheduleDialog : public QDialog, Ui::ImportScheduleDialog
{
    Q_OBJECT
    public:
        ImportScheduleDialog(SqlEngine *aSqlEngine, QWidget *aParent = NULL);
        ~ImportScheduleDialog();
    private slots:
        void searchSchedule();
        void importSchedule();
        void showParsingProgress(int progress);
    private:
        ScheduleXmlParser *mXmlParser;
        SqlEngine *mSqlEngine; // uses it
        QString mScheduleFileName;
};

#endif /* IMPORTSCHEDULEDIALOG_H */


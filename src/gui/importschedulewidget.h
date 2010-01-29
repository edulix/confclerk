#ifndef IMPORTSCHEDULEWIDGET_H
#define IMPORTSCHEDULEWIDGET_H

#include <QWidget>
#include "ui_importschedulewidget.h"

class ScheduleXmlParser;
class QNetworkAccessManager;
class QNetworkReply;

class ImportScheduleWidget : public QWidget, Ui::ImportScheduleWidget
{
    Q_OBJECT
    public:
        ImportScheduleWidget(QWidget *aParent = NULL);
        ~ImportScheduleWidget();
    private slots:
        void browseSchedule();
        void parsingSchedule(const QString &aTitle);
        void showParsingProgress(int progress);
        void networkQueryFinished(QNetworkReply *aReply);
        void downloadSchedule();
        void setupProxy();
    signals:
        void scheduleImported(int confId);
    private:
        void importData(const QByteArray &aData);
    private:
        ScheduleXmlParser *mXmlParser;
        QNetworkAccessManager *mNetworkAccessManager;
};

#endif /* IMPORTSCHEDULEWIDGET_H */


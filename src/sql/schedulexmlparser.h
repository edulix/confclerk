#ifndef SCHEDULEXMLPARSER_H_
#define SCHEDULEXMLPARSER_H_

#include <QObject>

class ScheduleXmlParser : public QObject
{
    Q_OBJECT
    public:
        ScheduleXmlParser (QObject *aParent = NULL);

    public slots:
        int parseData(const QByteArray &aData); // returns 'confId' of parsed conference schedule

    signals:
        void progressStatus(int aStatus);
        void parsingSchedule(const QString &aTitle);
};

#endif /* SCHEDULEXMLPARSER_H_ */


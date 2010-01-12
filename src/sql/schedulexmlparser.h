#ifndef SCHEDULEXMLPARSER_H_
#define SCHEDULEXMLPARSER_H_

#include <QObject>

class SqlEngine;

class ScheduleXmlParser : public QObject
{
    Q_OBJECT
    public:
        ScheduleXmlParser (QObject *aParent = NULL);

    public slots:
        void parseData(const QByteArray &aData, SqlEngine *aDBEngine);

    signals:
        void progressStatus(int aStatus);
};

#endif /* SCHEDULEXMLPARSER_H_ */


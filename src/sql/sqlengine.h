#ifndef SQLENGINE_H
#define SQLENGINE_H

#include <QObject>
#include <QHash>

class QSqlDatabase;

class SqlEngine : public QObject
{
    Q_OBJECT
    public:
        SqlEngine(QObject *aParent = NULL);
        ~SqlEngine();
        static void initialize();
        static void addConferenceToDB(QHash<QString,QString> &aConference);
        static void addEventToDB(QHash<QString,QString> &aEvent);
        static void addPersonToDB(QHash<QString,QString> &aPerson);
        static void addLinkToDB(QHash<QString,QString> &aLink);
        static void addRoomToDB(QHash<QString,QString> &aRoom);

        // search Events for ....
        static int searchEvent(int conferenceId, const QHash<QString,QString> &columns, const QString &keyword);
    private:
        static QString login(const QString &aDatabaseType, const QString &aDatabaseName);
        static bool createTables(QSqlDatabase &aDatabase);
        static bool execQuery(QSqlDatabase &aDatabase, const QString &aQuery);
};

#endif /* SQLENGINE_H */


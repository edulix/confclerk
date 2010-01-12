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
        void initialize();
        void addConferenceToDB(QHash<QString,QString> &aConference);
        void addEventToDB(QHash<QString,QString> &aEvent);
        void addPersonToDB(QHash<QString,QString> &aPerson);
        void addLinkToDB(QHash<QString,QString> &aLink);
        void addRoomToDB(QHash<QString,QString> &aRoom);
    private:
        QString login(const QString &aDatabaseType, const QString &aDatabaseName);
        bool createTables(QSqlDatabase &aDatabase);
};

#endif /* SQLENGINE_H */


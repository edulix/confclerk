#ifndef EVENT_H
#define EVENT_H

#include <QDateTime>
#include <QVector>
#include <QStringList>

#include <ormrecord.h>

/**
  NoSuchEventException is thrown when required event does not exist.
*/
class NoSuchEventException
{
};

class Event : public OrmRecord<Event>
{
public:
    static QSqlRecord const sColumns;
    //static QString const sTableName;
    static QString const sTable1Name;
    static QString const sTable2Name;
    static int const sTable1ColCount;
    static int const sTable2ColCount;

public:
    static Event getById(int id, int conferenceId);
    static QList<Event> getByDate(const QDate& date, int conferenceId);
    static QList<Event> getFavByDate(const QDate& date, int conferenceId); // get Favourities by Date

public:
    // Table 1
    int id() const { return value("id").toInt(); }
    int conferenceId() const { return value("xid_conference").toInt(); }
    QDateTime start() const { return value("start").toDateTime(); }
    int duration() const { return value("duration").toInt(); }
    int activityId() const { return value("xid_activity").toInt(); }
    QString type() const { return value("type").toString(); }
    QString language() const { return value("language").toString(); }
    bool isFavourite() const { return value("favourite").toBool(); }
    // Table 2 : virtual table for FTS (Full Text Search)
    QString tag() const { return value("tag").toString(); }
    QString title() const { return value("title").toString(); }
    QString subtitle() const { return value("subtitle").toString(); }
    QString abstract() const { return value("abstract").toString(); }
    QString description() const { return value("description").toString(); }

    // Table 1
    void setId(int id) { setValue("id", id); }
    void setConferenceId(int conferenceId) { setValue("xid_conference", conferenceId); }
    void setStart(const QDateTime& start) { setValue("start", start); }
    void setDuration(int duration) { setValue("duration", duration); }
    void setActivityId(int activityId) { setValue("xid_activity", activityId); }
    void setType(const QString& type) { setValue("type", type); }
    void setLanguage(const QString& language) { setValue("language", language); }
    void setFavourite(bool favourite) { setValue("favourite", (int)favourite); }
    // Table 2 : virtual table for FTS (Full Text Search)
    void setTag(const QString& tag) { setValue("tag", tag); }
    void setTitle(const QString& title) { setValue("title", title); }
    void setSubtitle(const QString& subtitle) { setValue("subtitle", subtitle); }
    void setAbstract(const QString& abstract) { setValue("abstract", abstract); }
    void setDescription(const QString& description) { setValue("description", description); }

friend class EventTest;
};

#endif // EVENT_H


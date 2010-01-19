/*
 * activity.h
 *
 *  Created on: Dec 27, 2009
 *      Author: Pavol Korinek
 */

#ifndef ACTIVITY_H_
#define ACTIVITY_H_

#include <ormrecord.h>

class Activity : public OrmRecord<Activity>
{
public:
    static const QSqlRecord sColumns;
    static QString const sTableName;
    static const int sTableColCount;
public:
    static QList<Activity> getAll();
    int id() const { return value("id").toInt(); }
    void setId(int id) { setValue("id", id); }
    QString name() const { return value("name").toString(); }
    void setName(const QString & type) { setValue("name", type); }
public:
    static void updateActivityMap();
    static QString getActivityName(int id);
private:
    static QMap<int, Activity>* mIdToActivity;
};

#endif /* ACTIVITY_H_ */

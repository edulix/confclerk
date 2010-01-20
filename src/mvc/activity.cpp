/*
 * activity.cpp
 *
 *  Created on: Dec 27, 2009
 *      Author: Pavol Korinek
 */

#include "activity.h"

QString const Activity::sTableName = QString("activity");
int const Activity::sTableColCount = 2;

QSqlRecord const Activity::sColumns = Activity::toRecord(QList<QSqlField>()
    << QSqlField("id", QVariant::Int)
    << QSqlField("name", QVariant::String));

QMap<int, Activity> Activity::mIdToActivity;

QList<Activity> Activity::getAll()
{
    QSqlQuery query;
    query.prepare(selectQuery());
    return load(query);
}

void Activity::updateActivityMap()
{
    mIdToActivity.clear();
    QList<Activity> activityList = Activity::getAll();
    Activity activity;
    for (int id = 0; id < activityList.count(); ++id) {
        activity = activityList.at(id);
        mIdToActivity.insert(activity.id(), activity);
    }
}

QString Activity::getActivityName(int id)
{
    QString name = mIdToActivity.value(id).name();
    if (name == "") {
        qDebug() << QString("Error: undefined activity name for id %1").arg(id);
    }
    return name;
}

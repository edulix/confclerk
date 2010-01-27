
#include "track.h"

QString const Track::sTableName = QString("track");
int const Track::sTableColCount = 2;
const QString Track::NAME = "name";

QSqlRecord const Track::sColumns = Track::toRecord(QList<QSqlField>()
    << QSqlField("id", QVariant::Int)
    << QSqlField(NAME, QVariant::String));

class TrackInsertException : OrmSqlException
{
public:
    TrackInsertException(const QString& text) : OrmSqlException(text) {}
};

int Track::insert()
{
    QSqlQuery query;
    query.prepare("INSERT INTO " + sTableName + " (" + NAME + ")" + " VALUES " + "(\"" + name() + "\")");
    if (!query.exec())
    {
        throw TrackInsertException("Exec Error");
    }
    QVariant variant = query.lastInsertId();
    if (variant.isValid())
        return variant.toInt();
    else
        throw TrackInsertException("Last Insert Id Error");
}

Track Track::retrieveByName(QString name)
{
    QSqlQuery query;
    query.prepare(
            selectQuery()
            + QString("WHERE %1.name = :name").arg(sTableName));
    query.bindValue(":name", name);
    return loadOne(query);
}

QList<Track> Track::getAll()
{
    QSqlQuery query;
    query.prepare(selectQuery());
    return load(query);
}

Track Track::retrieve(int id)
{
    QSqlQuery query;
    query.prepare(selectQuery()
            + QString("WHERE %1.id = :id").arg(sTableName));
    query.bindValue(":id", id);
    return loadOne(query);
}

QString Track::retrieveTrackName(int id)
{
    Track track = retrieve(id);
    return track.name();
}

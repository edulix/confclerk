#ifndef ORMRECORD_H
#define ORMRECORD_H

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>
#include <QStringList>
#include <QDateTime>
#include <QDebug>

class OrmException
{
};

class OrmNoObjectException : OrmException
{
};

class OrmSqlException : OrmException
{
public:
    OrmSqlException(const QString& text) : mText(text) {}
    QString text() const { return mText; }

private:
    QString mText;
};

template <typename T>
class OrmRecord : protected QSqlRecord
{
public:
    OrmRecord();
    static T hydrate(const QSqlRecord& record);

protected:
    QVariant value(QString col) const;
    void setValue(QString col, QVariant value);

    static T loadOne(QSqlQuery query);
    static QList<T> load(QSqlQuery query);

    // auxiliary methods
    static QString columnsForSelect(const QString& prefix = QString());
    static QString selectQuery();
    static QSqlRecord toRecord(const QList<QSqlField> & columnList);

    static QVariant convertToC(QVariant value, QVariant::Type colType);
    static QVariant convertToDb(QVariant value, QVariant::Type colType);
};

template <typename T>
OrmRecord<T>::OrmRecord()
{
    QSqlRecord::operator=(T::sColumns);
}

template <typename T>
T OrmRecord<T>::hydrate(const QSqlRecord& record)
{
    T object;
    object.QSqlRecord::operator=(record);
    return object;
}

template <typename T>
QVariant OrmRecord<T>::value(QString col) const
{
    return convertToC(QSqlRecord::value(col), T::sColumns.field(col).type());
}

template <typename T>
void OrmRecord<T>::setValue(QString col, QVariant value)
{
    QSqlRecord::setValue(col, convertToDb(value, T::sColumns.field(col).type()));
}

template <typename T>
T OrmRecord<T>::loadOne(QSqlQuery query)
{
    if (!query.isActive())
    {
        if (!query.exec())
        {
            throw new OrmSqlException(query.lastError().text());
        }
    }

    if (!query.next())
    {
        throw new OrmNoObjectException();
    }

    return hydrate(query.record());
}

template <typename T>
QList<T> OrmRecord<T>::load(QSqlQuery query)
{
    if (!query.isActive())
    {
        if (!query.exec())
        {
            throw new OrmSqlException(query.lastError().text());
        }
    }

    QList<T> objects;
    while (query.next())
    {
        objects << hydrate(query.record());
    }

    return objects;
}

template <typename T>
QString OrmRecord<T>::columnsForSelect(const QString& prefix)
{
    QStringList prefixedColumns;
    for (int i=0; i<T::sColumns.count(); i++)
    {
        prefixedColumns.append(prefix.isEmpty() ?
            T::sColumns.field(i).name() :
            QString("%1.%2").arg(prefix, T::sColumns.field(i).name()));
    }
    return prefixedColumns.join(",");
}

template <typename T>
QString OrmRecord<T>::selectQuery()
{
    return QString("SELECT %1 FROM %2 ").arg(columnsForSelect(), T::sTableName);
}

template <typename T>
QSqlRecord OrmRecord<T>::toRecord(const QList<QSqlField> & columnList)
{
    QSqlRecord record;
    foreach (const QSqlField & col, columnList)
    {
        record.append(col);
    }
    return record;
}

template <typename T>
QVariant OrmRecord<T>::convertToC(QVariant value, QVariant::Type colType)
{
    if (colType == QVariant::DateTime && value.canConvert<uint>())
    {
        QDateTime date;
        date.setTimeSpec(Qt::UTC);
        date.setTime_t(value.toUInt());
        return date;
    }

    return value;
}

template <typename T>
QVariant OrmRecord<T>::convertToDb(QVariant value, QVariant::Type colType)
{
    if (colType == QVariant::DateTime && value.canConvert<QDateTime>())
    {
        return value.toDateTime().toTime_t();
    }

    return value;
}

#endif // ORMRECORD_H

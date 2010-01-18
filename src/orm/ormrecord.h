#ifndef ORMRECORD_H
#define ORMRECORD_H

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>
#include <QStringList>
#include <QDateTime>
#include <QDebug>

// INFO:
// all record items/columns may be defined in one table (1.), or
// they can be splitted in two separate tables (2.) (eg. for FTS support)
// 1.) you have to define "static QString const sTableName"
// 2.) you have to define two table names:
//     "static QString const sTable1Name"
//     "static QString const sTable2Name"
// and since all record items/columns are handled by one QSqlRecord,
// you have to also define number of columns that belongs to table 1 (1.), and table 2 (2.)
// 1.) "static int const sTable1ColCount"
// 2.) "static int const sTable2ColCount"
// there are also defined auxiliary methods for 1-Table/2-Tables approach, see bellow

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
    void update(QString col, QVariant value = QVariant()); // updates specified column 'col'

protected:
    QVariant value(QString col) const;
    void setValue(QString col, QVariant value);

    static T loadOne(QSqlQuery query);
    static QList<T> load(QSqlQuery query);

    // auxiliary methods
    static QSqlRecord toRecord(const QList<QSqlField> & columnList);
    // all record items/columns are in one table
    static QString columnsForSelect(const QString& prefix = QString());
    static QString selectQuery();
    static QString updateQuery();
    // record items/columns are stored in two tables
    static QString columnsForSelectJoin2T(); // for joining two tables
    static QString selectQueryJoin2T(const QString &key); // for joining two tables

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

// updates specified column 'col'
// if the value is not specified  as an argument,
// it's taken from the reford itself
// see also: setValue() method for more details
template <typename T>
void OrmRecord<T>::update(QString col, QVariant value)
{
    QSqlQuery query;
    query.prepare(QString(updateQuery() + "SET %1 = :col WHERE id = :id").arg(col));
    if(value.isValid()) // take 'col' value from the method's arguments
        query.bindValue(":col", value);
    else // take 'col' value from the record; see setValue()
        query.bindValue(":col", convertToDb(this->value(col), this->value(col).type()));
    query.bindValue(":id", this->value("id"));
    //query.bindValue(":id", convertToDb(value("id"), QVariant::Int));
    query.exec();
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
QString OrmRecord<T>::columnsForSelectJoin2T()
{
    Q_ASSERT((T::sTable1ColCount+T::sTable2ColCount) == T::sColumns.count());

    QStringList prefixedColumns;
    for (int i=0; i<T::sTable1ColCount; i++)
    {
        prefixedColumns.append(QString("%1.%2").arg(T::sTable1Name, T::sColumns.field(i).name()));
    }
    for (int j=0; j<T::sTable2ColCount; j++)
    {
        prefixedColumns.append(QString("%1.%2").arg(T::sTable2Name, T::sColumns.field(T::sTable1ColCount+j).name()));
    }
    return prefixedColumns.join(",");
}

template <typename T>
QString OrmRecord<T>::selectQuery()
{
    return QString("SELECT %1 FROM %2 ").arg(columnsForSelect(), T::sTableName);
}


template <typename T>
QString OrmRecord<T>::selectQueryJoin2T(const QString &key)
{
    return QString("SELECT %1 FROM %2 INNER JOIN %3 ON %4.%5 = %6.%7 ").arg(
            columnsForSelectJoin2T(),
            T::sTable1Name,
            T::sTable2Name,
            T::sTable1Name,
            key,
            T::sTable2Name,
            key);
}

template <typename T>
QString OrmRecord<T>::updateQuery()
{
    return QString("UPDATE %1 ").arg(T::sTable1Name);
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


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
public:
    OrmException(const QString& text) : mText(text) {};
    virtual ~OrmException(){};
    virtual const QString& text() const { return mText; }
private:
    QString mText;
};

class OrmNoObjectException : public OrmException
{
public:
    OrmNoObjectException() : OrmException("No object exception"){};
    ~OrmNoObjectException(){};
};

class OrmSqlException : public OrmException
{
public:
    OrmSqlException(const QString& text) : OrmException( QString("Sql error: ") + text ) {};
    ~OrmSqlException(){};
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
            throw OrmSqlException(query.lastError().text());
        }
    }

    if (!query.next())
    {
        throw OrmNoObjectException();
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
            qDebug() << "Error: " << query.lastError().driverText() << "; Type: " << query.lastError().type();
            throw OrmSqlException(query.lastError().text());
        }
        else
        {
            qDebug() << "SQL OK";
        }
    }

    QList<T> objects;
    while (query.next())
    {
        objects << hydrate(query.record());
    }
    qDebug() << "Fetch done";
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
QString OrmRecord<T>::updateQuery()
{
    return QString("UPDATE %1 ").arg(T::sTableName);
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


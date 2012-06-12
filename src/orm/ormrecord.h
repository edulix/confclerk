/*
 * Copyright (C) 2010 Ixonos Plc.
 * Copyright (C) 2011-2012 Philipp Spitzer, gregor herrmann, Stefan Stahl
 *
 * This file is part of ConfClerk.
 *
 * ConfClerk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option)
 * any later version.
 *
 * ConfClerk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * ConfClerk.  If not, see <http://www.gnu.org/licenses/>.
 */
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
    OrmException(const QString& text) : mText(text) {}
    virtual ~OrmException(){}
    virtual const QString& text() const { return mText; }
private:
    QString mText;
};

class OrmNoObjectException : public OrmException
{
public:
    OrmNoObjectException() : OrmException("No object exception"){}
    ~OrmNoObjectException(){}
};

class OrmSqlException : public OrmException
{
public:
    OrmSqlException(const QString& text) : OrmException( QString("Sql error: ") + text ) {}
    ~OrmSqlException(){}
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
// if the value is not specified as an argument,
// it's taken from the record itself
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
QString OrmRecord<T>::updateQuery()
{
    return QString("UPDATE %1 ").arg(T::sTableName);
}

template <typename T>
QSqlRecord OrmRecord<T>::toRecord(const QList<QSqlField> & columnList)
{
    QSqlRecord record;
    for(int i=0; i< columnList.count(); i++)
    {
        record.append(columnList[i]);
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
        QDateTime dateTime = value.toDateTime();
        dateTime.setTimeSpec(Qt::UTC); // this is to avoid that dateTime.toTime_t changes the time depending on the local time zone
        return dateTime.toTime_t();
    }

    return value;
}

#endif // ORMRECORD_H


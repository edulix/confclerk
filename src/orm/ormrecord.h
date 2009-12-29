#include <QSqlRecord>
#include <QSqlField>

template <typename T>
class OrmRecord : protected QSqlRecord
{
public:
    static QString colName(int col);

protected:
    QVariant value(int col) const;
    void setValue(int col, QVariant value);
};

template <typename T>
QString OrmRecord<T>::colName(int col)
{
    return T::sColNames.at(col);
}

template <typename T>
QVariant OrmRecord<T>::value(int col) const
{
    Q_ASSERT(col >= 0 && col < T::sColNames.count());

    return QSqlRecord::value(T::sColNames.at(col));
}

template <typename T>
void OrmRecord<T>::setValue(int col, QVariant value)
{
    Q_ASSERT(col >= 0 && col < T::sColNames.count());

    QString fieldName = T::sColNames.at(col);

    if (!contains(fieldName))
    {
        append(QSqlField(fieldName, value.type()));
    }

    QSqlRecord::setValue(fieldName, value);
}

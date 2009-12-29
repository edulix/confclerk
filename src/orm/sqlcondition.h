#ifndef SQLCONDITION_H
#define SQLCONDITION_H

//#include <QVariant>

//class SqlCondition
//{
//public:
//    enum Operator { eq = 0, ne, gt, ge, lt, le };
//
//public:
//    SqlCondition(const QLatin1String& column, Operator op, const QVariant& value) :
//            mColumn(column), mValue(value), mOperator(op) {}
//
//    virtual QString toString() const;
//private:
//    QLatin1String mColumn;
//    QVariant mValue;
//    Operator mOperator;
//
//private:
//    static char* sOperatorNames[];
//};
//
//class SqlAndCondition : public SqlCondition
//{
//    SqlCondition mLeft;
//    SqlCondition mRight;
//
//public:
//    SqlAndCondition(const SqlCondition& left, const SqlCondition& right):
//            mLeft(left), mRight(right) {}
//
//    QString toString() const;
//};
//
//class SqlOrCondition : public SqlCondition
//{
//    SqlCondition mLeft;
//    SqlCondition mRight;
//
//public:
//    SqlOrCondition(const SqlCondition& left, const SqlCondition& right):
//            mLeft(left), mRight(right) {}
//
//    QString toString() const;
//};
//
//class SqlNotCondition : public SqlCondition
//{
//    SqlCondition mCond;
//public:
//    SqlNotCondition(const SqlCondition& cond): mCond(new SqlCondition(cond)) {}
//
//    QString toString() const;
//};
//
//class SqlColumn
//{
//public:
//    SqlColumn(const QLatin1String& column) : mColumn(column) {}
//
//    SqlCondition const operator==(const QVariant& value) { return SqlCondition(mColumn, SqlCondition::eq, value); }
//    SqlCondition const operator!=(const QVariant& value) { return SqlCondition(mColumn, SqlCondition::ne, value); }
//    SqlCondition const operator>=(const QVariant& value) { return SqlCondition(mColumn, SqlCondition::ge, value); }
//    SqlCondition const operator> (const QVariant& value) { return SqlCondition(mColumn, SqlCondition::gt, value); }
//    SqlCondition const operator<=(const QVariant& value) { return SqlCondition(mColumn, SqlCondition::le, value); }
//    SqlCondition const operator< (const QVariant& value) { return SqlCondition(mColumn, SqlCondition::lt, value); }
//private:
//    QLatin1String mColumn;
//};


#endif // SQLCONDITION_H

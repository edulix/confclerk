#ifndef EVENTTEST_H
#define EVENTTEST_H

#include <QObject>

class EventTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();

    void getById();
    void colNames();
    void storingValues();
};


#endif // EVENTTEST_H


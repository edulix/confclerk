#ifndef EVENTTEST_H
#define EVENTTEST_H

#include <QObject>

class EventTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();

    void getById();
    void storingValues();
    void hydrate();
    void columnsForSelect();
    void selectQuery();
};


#endif // EVENTTEST_H


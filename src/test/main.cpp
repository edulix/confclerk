#include <QtTest>

#include "model/eventtest.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    EventTest eventTest;
    QTest::qExec(&eventTest, argc, argv);
}


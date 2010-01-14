#include <QtTest>

#include "mvc/eventtest.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    EventTest eventTest;
    QTest::qExec(&eventTest, argc, argv);
}


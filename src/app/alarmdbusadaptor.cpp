
#include "alarmdbusadaptorp.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>


AlarmDBusAdaptor::AlarmDBusAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

AlarmDBusAdaptor::~AlarmDBusAdaptor()
{
    // destructor
}

void AlarmDBusAdaptor::Alarm(int aEventId)
{
    QMetaObject::invokeMethod(parent(), "Alarm",Q_ARG(int, aEventId));
}



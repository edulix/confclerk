#ifndef ALARM_DBUS_ADAPTOR_P_H
#define ALARM_DBUS_ADAPTOR_P_H

#include <QtCore/QObject>
#include <QtDBus/QtDBus>

QT_BEGIN_NAMESPACE
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;
QT_END_NAMESPACE


class AlarmDBusAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.fosdem.schedule.AlarmInterface")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"org.fosdem.schedule.AlarmInterface\" >\n"
"  <method name=\"Alarm\">\n"
"	  <arg name=\"aEventId\" type=\"i\" direction=\"in\"/>\n"
"  </method>\n"
"  </interface>\n"
        "")
public:
	AlarmDBusAdaptor(QObject *parent);
    virtual ~AlarmDBusAdaptor();

public: // PROPERTIES
public Q_SLOTS: // METHODS
	void Alarm(int aEventId);
};

#endif

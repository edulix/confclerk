#ifndef SINGLE_INSTANCE_H
#define SINGLE_INSTANCE_H

#include <QObject>
#include <QtDBus/QtDBus>

class CAlarmDBus: public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.fosdem.schedule")

public:
	CAlarmDBus(QWidget * aParent);
    virtual ~CAlarmDBus();

public: // PROPERTIES
public Q_SLOTS: // METHODS
    void Alarm(int aEventId);
private:
	QWidget * mParent;
};


#endif // SINGLE_INSTANCE_H

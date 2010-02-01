
#include "alarmdbus.h"
#include "eventdialog.h"




CAlarmDBus::CAlarmDBus(QWidget * aParent)
    : QObject(),
    mParent(aParent)
{
    // constructor
    //setAutoRelaySignals(true);
}

CAlarmDBus::~CAlarmDBus()
{
    // destructor
}

void CAlarmDBus::Alarm(int aEventId)
{
	EventDialog dialog(aEventId,mParent);
	dialog.exec();

}

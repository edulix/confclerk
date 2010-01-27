#include "eventdialog.h"
#include <conference.h>

#include <QScrollBar>

#ifdef MAEMO
#include <alarm.h>
#endif

EventDialog::EventDialog(const int &aEventId, QWidget *aParent)
    : QDialog(aParent)
    , mEventId(aEventId)
{
    setupUi(this);

#ifdef MAEMO
    showFullScreen();
#endif

    Event event = Event::getById(mEventId,Conference::activeConference());

    title->setText(event.title());
    persons->setText(event.persons().join(" and "));
    abstract->setText(event.abstract());
    description->setText(event.description());
    links->setText(static_cast<QStringList>(event.links().values()).join("\n"));

    connect(favouriteButton, SIGNAL(clicked()), SLOT(favouriteClicked()));
    connect(alarmButton, SIGNAL(clicked()), SLOT(alarmClicked()));

    if(event.isFavourite())
    {
        favouriteButton->setIcon(QIcon(":/icons/favourite-onBig.png"));
    }

    if(event.hasAlarm())
    {
        alarmButton->setIcon(QIcon(":/icons/alarm-onBig.png"));
    }
}

void EventDialog::favouriteClicked()
{
    Event event = Event::getById(mEventId,Conference::activeConference());

    if(event.isFavourite())
    {
        event.setFavourite(false);
        favouriteButton->setIcon(QIcon(":/icons/favourite-offBig.png"));
    }
    else
    {
        event.setFavourite(true);
        favouriteButton->setIcon(QIcon(":/icons/favourite-onBig.png"));
    }
    event.update("favourite");
    qDebug() << " FAVOURITE [" << event.id() << "] -> " << event.isFavourite();
    // update EVENT_CONFLICT table
    event.updateConflicts();
    // since the Favourite icon has changed, update TreeViews accordingly
    // all TreeViews have to listen on this signal
    emit(eventHasChanged(event.id()));
}

void EventDialog::alarmClicked()
{
    Event event = Event::getById(mEventId,Conference::activeConference());

    if(event.hasAlarm())
    {
        event.setHasAlarm(false); // update DB
        alarmButton->setIcon(QIcon(":/icons/alarm-offBig.png"));
#ifdef MAEMO
        // remove alarm from the 'alarmd' alrms list
        Alarm alarm;
        alarm.deleteAlarm(event.id());
        // TODO: test if removing was successfull
#endif /* MAEMO */
    }
    else
    {
        event.setHasAlarm(true);
        alarmButton->setIcon(QIcon(":/icons/alarm-onBig.png"));
#ifdef MAEMO
        // add alarm to the 'alarmd'
        Alarm alarm;
        int cookie = alarm.addAlarm(event.id(),QDateTime::currentDateTime().addSecs(10));
        qDebug() << "cookie: " << cookie;
#endif /* MAEMO */
    }
    event.update("alarm");
    qDebug() << " ALARM [" << event.id() << "] -> " << event.hasAlarm();
    // since the Alarm icon has changed, update TreeView accordingly
    // all TreeViews have to listen on this signal
    emit(eventHasChanged(event.id()));
}


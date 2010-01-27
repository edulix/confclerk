#include "eventdialog.h"
#include <appsettings.h>

#include <QScrollBar>

#ifdef MAEMO
#include <alarm.h>
#endif

DetailsContainer::DetailsContainer(QWidget *aParent)
    : QWidget(aParent)
{
    mAbstract.setWordWrap(true);
    mDescription.setWordWrap(true);

    QFont f = QLabel().font();
    f.setBold(true);
    f.setItalic(true);
    mMainLayout = new QVBoxLayout(this);
    QLabel *persons = new QLabel("Persons:");
    persons->setFont(f);
    mMainLayout->addWidget(persons);
    mMainLayout->addWidget(&mPersons);
    mMainLayout->addWidget(new QLabel("")); // spacer
    QLabel *abstract = new QLabel("Abstract:");
    abstract->setFont(f);
    mMainLayout->addWidget(abstract);
    mMainLayout->addWidget(&mAbstract);
    mMainLayout->addWidget(new QLabel("")); // spacer
    QLabel *description = new QLabel("Description:");
    description->setFont(f);
    mMainLayout->addWidget(description);
    mMainLayout->addWidget(&mDescription);
    setLayout(mMainLayout);
}

void DetailsContainer::setPersons(const QStringList &aPersons)
{
    mPersons.setText(aPersons.join(" and "));
}

void DetailsContainer::setAbstract(const QString &aAbstract)
{
    mAbstract.setText(aAbstract);
}

void DetailsContainer::setDescription(const QString &aDescription)
{
    mDescription.setText(aDescription);
}

EventDialog::EventDialog(const int &aEventId, QWidget *aParent)
    : QDialog(aParent)
    , mEventId(aEventId)
{
    setupUi(this);

#ifdef MAEMO
    showFullScreen();
#endif

    Event event = Event::getById(mEventId,AppSettings::confId());

    title->setText(event.title());
    mDetails.setPersons(event.persons());
    mDetails.setAbstract(event.abstract());
    mDetails.setDescription(event.description());
    scrollArea->setWidget(&mDetails);

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
    Event event = Event::getById(mEventId,AppSettings::confId());

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
    Event event = Event::getById(mEventId,AppSettings::confId());

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


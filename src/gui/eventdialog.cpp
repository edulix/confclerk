#include "eventdialog.h"
#include <appsettings.h>

#include <QScrollBar>

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

    Event event = Event::getById(aEventId,AppSettings::confId());

    title->setText(event.title());
    mDetails.setPersons(event.persons());
    mDetails.setAbstract(event.abstract());
    mDetails.setDescription(event.description());
    scrollArea->setWidget(&mDetails);
}


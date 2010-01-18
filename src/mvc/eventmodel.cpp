#include "eventmodel.h"
#include <conference.h>

EventModel::EventModel()
{
    mEvents.clear();
}

void EventModel::createTimeGroups()
{
    mGroups.clear();
    mParents.clear();

    if (mEvents.empty())
    {
        return;
    }

    const int timeSpan = 5400;

    QTime startTime = mEvents.first().start().time();
    mGroups << EventModel::Group(QString("%1 - %2").arg(startTime.toString("HH:mm"),
        startTime.addSecs(timeSpan).toString("HH:mm")), 0);
    QTime nextGroupTime = mEvents.first().start().time().addSecs(timeSpan);

    for (int i=0; i<mEvents.count(); i++)
    {
        QTime eventTime = mEvents.at(i).start().time();

        if (nextGroupTime <= eventTime)
        {
            mGroups.last().mChildCount = i - mGroups.last().mFirstEventIndex;
            mGroups << EventModel::Group(QString("%1 - %2").arg(nextGroupTime.toString("HH:mm"),
                nextGroupTime.addSecs(timeSpan).toString("HH:mm")), i);
            nextGroupTime = nextGroupTime.addSecs(timeSpan);
        }

        // add parent-child relation
        mParents[mEvents.at(i).id()] = mGroups.count() - 1;
    }

    mGroups.last().mChildCount = mEvents.count() - mGroups.last().mFirstEventIndex;
}

void EventModel::createActivityGroups() {
    mGroups.clear();
    mParents.clear();
    if (mEvents.empty())
    {
        return;
    }
    int activityId = mEvents.first().activityId();
    //TODO korinpa: get activity name
    mGroups << EventModel::Group(QString("activity %1").arg(activityId), 0);
    int nextActivityId = activityId;

    for (int i=0; i<mEvents.count(); i++)
    {
        activityId = mEvents.at(i).activityId();
        if (nextActivityId != activityId)
        {
            mGroups.last().mChildCount = i - mGroups.last().mFirstEventIndex;
            mGroups << EventModel::Group(QString("activity %1").arg(activityId), 0);
            int nextActivityId = activityId;
        }
        // add parent-child relation
        mParents[mEvents.at(i).id()] = mGroups.count() - 1;
    }
    mGroups.last().mChildCount = mEvents.count() - mGroups.last().mFirstEventIndex;
}

QVariant EventModel::data(const QModelIndex& index, int role) const
{
    if (index.isValid() && role == Qt::DisplayRole)
    {
        if (index.internalId() == 0)
        {
            return mGroups.at(index.row()).mTitle;
        }
        else //event data
        {
            return static_cast<Event*>(index.internalPointer())->id();
        }
    }

    return QVariant();
}

QModelIndex EventModel::index(int row, int column, const QModelIndex& parent) const
{
    // TODO: add checks for out of range rows

    if (!parent.isValid())
    {
        return createIndex(row, column, 0);
    }
    else if (parent.internalId() == 0)
    {
        const Group& group = mGroups.at(parent.row());
        Event* event = const_cast<Event*>(&mEvents.at(row + group.mFirstEventIndex));
        return createIndex(row, column, reinterpret_cast<void*>(event));
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex EventModel::parent(const QModelIndex & index) const
{
    if (index.isValid())
    {
        if (index.internalId() == 0)
        {
            return QModelIndex();
        }

        Event * event = static_cast<Event*>(index.internalPointer());

        return createIndex(mParents[event->id()], 0, 0);
    }

    return QModelIndex();
}

int EventModel::columnCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return 1;
}

int EventModel::rowCount (const QModelIndex & parent) const
{
    if (!parent.isValid())
    {
        return mGroups.count();
    }

    if (parent.internalId() == 0)
    {
        return mGroups.at(parent.row()).mChildCount;
    }

    return 0;
}

void EventModel::clearModel()
{
    for(int i = 0;i < mGroups.count();i++){
        QModelIndex idx = index(i, 0);
        Group group = mGroups[i];
        beginRemoveRows(idx, 0, group.mChildCount - 1);
        bool ok = removeRows(0, group.mChildCount, idx);
        endRemoveRows();
        //qDebug() << "removing " << group.mChildCount << " events from group:" << i << idx.data() << ":" << ok;
    }
    mEvents.clear();
}

void EventModel::loadEvents(const QDate &aDate, int aConferenceId)
{
    clearModel();
    // check for existence of the conference in the DB
    if(Conference::getAll().count())
    {
        qDebug() << "Loading Conference Data: [" << Conference::getById(aConferenceId).title() << "] " << aDate;
        mEvents = Event::getByDate(QDate(aDate.year(), aDate.month(), aDate.day()), aConferenceId);
    }
    createTimeGroups();
}

void EventModel::loadFavEvents(const QDate &aDate, int aConferenceId)
{
    clearModel();
    // check for existence of the conference in the DB
    if(Conference::getAll().count())
    {
        qDebug() << "Loading FAV Conference Data: [" << Conference::getById(aConferenceId).title() << "] " << aDate;
        mEvents = Event::getFavByDate(QDate(aDate.year(), aDate.month(), aDate.day()), aConferenceId);
    }
    createTimeGroups();
}

void EventModel::loadEventsByActivities(const QDate &aDate, int aConferenceId)
{
    clearModel();
    if(Conference::getAll().count())
    {
        qDebug() << "Loading Conference Data (by Activities): [" << Conference::getById(aConferenceId).title() << "] " << aDate;
        mEvents = Event::getByDate(QDate(aDate.year(), aDate.month(), aDate.day()), aConferenceId);
    }
    createActivityGroups();
}

void EventModel::emitDataChangedSignal(const QModelIndex &aTopLeft, const QModelIndex &aBottomRight)
{
    emit(dataChanged(aTopLeft,aBottomRight));
}


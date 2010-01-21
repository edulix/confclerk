#ifndef EVENTMODEL_H
#define EVENTMODEL_H

#include <QAbstractItemModel>

#include "event.h"

class EventModel : public QAbstractItemModel
{
public:
    static const QString COMMA_SEPARATOR;
public:
    EventModel();
    QVariant data(const QModelIndex& index, int role) const;
    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    QModelIndex parent ( const QModelIndex & index ) const;
    int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    void loadEvents(const QDate &aDate, int aConferenceId); // loads Events from the DB
    void loadFavEvents(const QDate &aDate, int aConferenceId); // loads Favourite events from the DB
    void loadEventsByTrack(const QDate &aDate, int aConferenceId); // loads Events grouped by Track from the DB
    int loadSearchResultEvents(const QDate &aDate, int aConferenceId);

private:
    struct Group
    {
        Group(const QString & title,
              int firstEventIndex) :

            mTitle(title),
            mFirstEventIndex(firstEventIndex),
            mChildCount(0)
        {}

        QString mTitle;
        int mFirstEventIndex;
        int mChildCount;
    };

private:
    void createTimeGroups();
    void createTrackGroups();
    void clearModel();

public slots:
    void updateModel(int aEventId);

private:
    QList<Event> mEvents;
    QList<Group> mGroups;
    QHash<int, int> mParents;
};

#endif // EVENTMODEL_H


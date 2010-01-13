#ifndef EVENTMODEL_H
#define EVENTMODEL_H

#include <QAbstractItemModel>

#include "event.h"

class EventModel : public QAbstractItemModel
{
public:
    EventModel();
    QVariant data(const QModelIndex& index, int role) const;
    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    QModelIndex parent ( const QModelIndex & index ) const;
    int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    void loadEvents(); // loads Events from the DB

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

private:
    QList<Event> mEvents;
    QList<Group> mGroups;
    QHash<int, int> mParents;
    QDate mCurrentDate;
    int mConfId;
};

#endif // EVENTMODEL_H


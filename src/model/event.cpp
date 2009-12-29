#include "event.h"

QStringList const Event::sColNames = QStringList()
    << "id" << "xid_conference" << "start" << "duration" << "xid_activity" << "type" << "language";

QString const Event::sTableName = QString("event");

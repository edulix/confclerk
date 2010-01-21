#include "eventdialog.h"

#include <QScrollBar>

EventDialog::EventDialog(const int &aEventId, QWidget *aParent)
    : QDialog(aParent)
    , mEventId(aEventId)
{
    setupUi(this);

#ifdef MAEMO
    showFullScreen();
#endif

    const int confId = 1;
    Event event = Event::getById(aEventId,confId);

    //abstract->setStyleSheet("background-color : transparent;");
    //description->setStyleSheet("background-color : transparent;");

    // use text color from 'title' QLabel
    QColor color = title->palette().color(QPalette::Active, QPalette::WindowText);
    QColor bkgrColor = this->palette().color(QPalette::Active, QPalette::Background);
    QPalette p = abstract->palette();
    p.setColor(QPalette::Active, QPalette::Text, color);
    p.setColor(QPalette::Active, QPalette::Base, bkgrColor);
    abstract->setPalette(p);
    description->setPalette(p);

    // set scrollbars color
    //QPalette p2 = description->verticalScrollBar()->palette();
    //p2.setColor(QPalette::Active, QPalette::Background, color);
    ////description->verticalScrollBar()->setStyleSheet("background-color : blue;");
    //abstract->verticalScrollBar()->setPalette(p2);
    //description->verticalScrollBar()->setPalette(p2);

    title->setText(event.title());
    persons->setText(event.persons().join(" and "));
    abstract->setPlainText(event.abstract());
    description->setPlainText(event.description());
}


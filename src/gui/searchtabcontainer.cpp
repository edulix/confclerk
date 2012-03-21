/*
 * Copyright (C) 2010 Ixonos Plc.
 * Copyright (C) 2011-2012 Philipp Spitzer, gregor herrmann
 *
 * This file is part of ConfClerk.
 *
 * ConfClerk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option)
 * any later version.
 *
 * ConfClerk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * ConfClerk.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "searchtabcontainer.h"
#include "searchhead.h"
#include <QMessageBox>

SearchTabContainer::SearchTabContainer(QWidget *aParent) : TabContainer( aParent )
{
    header = new SearchHead(this);
    header->setObjectName(QString::fromUtf8("header"));
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    //sizePolicy.setHeightForWidth(TabContainer::sizePolicy().hasHeightForWidth());
    sizePolicy.setHeightForWidth(header->sizePolicy().hasHeightForWidth());
    header->setSizePolicy(sizePolicy);
    header->setMinimumSize(QSize(10, 10));
    verticalLayout->insertWidget(0,header);
    connect(header, SIGNAL(searchClicked()), SLOT(searchButtonClicked()));
    showSearchDialog();
}


bool SearchTabContainer::searchDialogIsVisible() const {
    return header->isVisible();
}


int SearchTabContainer::searchResultCount(const QDate& date) const {
    int confId = Conference::activeConference();
    if (confId == -1) return 0;
    return Event::getSearchResultByDate(date, confId, "start, duration").count();
}


void SearchTabContainer::showSearchDialog(bool show) {
    header->setVisible(show);
    treeView->setVisible(!show);
}


void SearchTabContainer::searchButtonClicked() {
    QHash<QString,QString> columns;

    SearchHead *searchHeader = static_cast<SearchHead*>(header);
    if( searchHeader->searchTitle->isChecked() )
        columns.insertMulti("EVENT", "title");
    if( searchHeader->searchAbstract->isChecked() )
        columns.insertMulti("EVENT", "abstract");
    if( searchHeader->searchTag->isChecked() )
        columns.insertMulti("EVENT", "tag");
    if( searchHeader->searchSpeaker->isChecked() )
        columns["PERSON"] = "name";
    if( searchHeader->searchRoom->isChecked() )
        columns["ROOM"] = "name";

    QString keyword = searchHeader->searchEdit->text();

    int confId = Conference::activeConference();
    if (confId == -1) return;
    Conference conf = Conference::getById(confId);

    SqlEngine::searchEvent( confId, columns, keyword );

    int nrofFounds = 0;
    for (QDate d = conf.start(); d <= conf.end(); d = d.addDays(1))
        nrofFounds += Event::getSearchResultByDate(d, confId, "start, duration").count();

    if (!nrofFounds) {
        treeView->hide();
        header->show();
        QMessageBox::information(
                this,
                QString("Keyword '%1' not found!").arg(keyword),
                QString("No events containing '%1' found!").arg(keyword),
                QMessageBox::Ok);
    } else {
        treeView->show();
        header->hide();

        emit searchResultChanged();
    }
}


void SearchTabContainer::loadEvents( const QDate &aDate, const int aConferenceId )
{
    static_cast<EventModel*>(treeView->model())->loadSearchResultEvents( aDate, aConferenceId );
}


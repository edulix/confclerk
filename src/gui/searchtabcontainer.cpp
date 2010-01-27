
#include "searchtabcontainer.h"
#include "searchhead.h"


SearchTabContainer::SearchTabContainer(QWidget *aParent) : TabContainer( aParent )
{
    header = new SearchHead(this);
    header->setObjectName(QString::fromUtf8("header"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    //sizePolicy.setHeightForWidth(TabContainer::sizePolicy().hasHeightForWidth());
    sizePolicy.setHeightForWidth(header->sizePolicy().hasHeightForWidth());
    header->setSizePolicy(sizePolicy);
    header->setMinimumSize(QSize(10, 10));

    verticalLayout->insertWidget(0,header);

    header->show();

    searchAgainButton = new QToolButton(this);
    searchAgainButton->setObjectName(QString::fromUtf8("button"));
    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/search.png")), QIcon::Normal, QIcon::Off);
    searchAgainButton->setIcon(icon);
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(searchAgainButton->sizePolicy().hasHeightForWidth());
    searchAgainButton->setSizePolicy(sizePolicy1);

    verticalLayout_2->insertWidget(0,searchAgainButton);

    searchAgainButton->show();

    connect( header, SIGNAL(searchClicked()), SLOT(searchButtonClicked()));
    connect( searchAgainButton, SIGNAL(clicked()), SLOT(searchAgainClicked()));
}

SearchTabContainer::~SearchTabContainer()
{
}

void SearchTabContainer::searchButtonClicked()
{
    qDebug() << "SearchTab::searchButtonClicked()";

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

    QString keyword = searchHeader->searchEdit->text().replace( QString("%"), QString("\\%") );
    qDebug() << "\nKeyword to search: " << keyword;

    int confId = Conference::activeConference();
    SqlEngine::searchEvent( confId, columns, keyword );

    QDate startDate = Conference::getById(confId).start();
    QDate endDate = Conference::getById(confId).end();
    dayNavigator->setDates(startDate, endDate);
    updateTreeView( Conference::getById(confId).start() );
}

void SearchTabContainer::searchAgainClicked()
{
    qDebug() << "SearchTab::searchAgainClicked()";
    header->show();
    searchAgainButton->hide();
    dayNavigator->hide();
    treeView->hide();
}

void SearchTabContainer::loadEvents( const QDate &aDate, const int aConferenceId )
{
    int eventsCount = static_cast<EventModel*>(treeView->model())->loadSearchResultEvents( aDate, aConferenceId );
    if( eventsCount ||
            //TODO: this is not good test
            dayNavigator->getCurrentDate() != Conference::getById( aConferenceId ).start()
            ){
        searchAgainButton->show();
        dayNavigator->show();
        treeView->show();
        header->hide();
    }
    else{
        treeView->hide();
        searchAgainButton->hide();
        dayNavigator->hide();
        header->show();
    }
}

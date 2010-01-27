
#include "searchhead.h"

SearchHead::SearchHead(QWidget *parent)
    : QWidget(parent)
{
	setupUi(this);
	connect( searchButton, SIGNAL(clicked()), SLOT(searchButtonClicked()));
}

SearchHead::~SearchHead()
{

}


void SearchHead::searchButtonClicked()
{
    qDebug() << "SearchHead::searchButtonClicked()";
    emit( searchClicked() );
}

#ifndef SEARCHHEAD_H
#define SEARCHHEAD_H

#include <QtGui/QWidget>
#include <QDebug>
#include "ui_searchhead.h"

class SearchHead : public QWidget, public Ui::SearchHeadClass
{
    Q_OBJECT

public:
    SearchHead(QWidget *parent = 0);
    ~SearchHead();

signals:
    void searchClicked();

private slots:
    void searchButtonClicked();

//private:
    //Ui::SearchHeadClass ui;
};

#endif // SEARCHHEAD_H

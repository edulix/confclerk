#include "importschedulewidget.h"

#include <schedulexmlparser.h>

#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QNetworkProxy>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>

const QString SCHEDULE_URL = "http://fosdem.org/2010/schedule/xml";

ImportScheduleWidget::ImportScheduleWidget(QWidget *aParent)
    : QWidget(aParent)
{
    setupUi(this);

    mXmlParser = new ScheduleXmlParser(this);
    connect(mXmlParser, SIGNAL(progressStatus(int)), SLOT(showParsingProgress(int)));
    connect(mXmlParser, SIGNAL(parsingSchedule(const QString &)), SLOT(parsingSchedule(const QString &)));

    connect(browse, SIGNAL(clicked()), SLOT(browseSchedule()));
    progressBar->hide();

    cancel->hide();
    importAction->hide();
    connect(online, SIGNAL(clicked()), SLOT(downloadSchedule()));

    mNetworkAccessManager = new QNetworkAccessManager(this);
    connect(mNetworkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(networkQueryFinished(QNetworkReply*)));
    mNetworkAccessManager->setProxy(QNetworkProxy::applicationProxy());
}

ImportScheduleWidget::~ImportScheduleWidget()
{
    if(mXmlParser)
    {
        delete mXmlParser;
        mXmlParser = NULL;
    }
    if(mNetworkAccessManager)
    {
        delete mNetworkAccessManager;
        mNetworkAccessManager = NULL;
    }
}

void ImportScheduleWidget::parsingSchedule(const QString &aTitle)
{
    importScheduleLabel->setText("Importing: " + aTitle);
}

void ImportScheduleWidget::showParsingProgress(int progress)
{
    progressBar->setValue(progress);
}

void ImportScheduleWidget::browseSchedule()
{
    QString scheduleFileName = QFileDialog::getOpenFileName(this, tr("Select Conference Schedule"), QDir::homePath(), tr("Schedule Files (*.xml)"));
    if(QFile::exists(scheduleFileName))
    {
        QFile file(scheduleFileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "can't open " << file.fileName();
            return;
        }

        importData(file.readAll());

    }
    else
    {
        progressBar->hide();
    }
}

void ImportScheduleWidget::networkQueryFinished(QNetworkReply *aReply)
{
    qDebug() << "ImportScheduleWidget::networkQueryFinished()";

    if ( aReply->error() != QNetworkReply::NoError )
    {
        qDebug() << "Error occured during download: " << aReply->errorString();
    }
    else
    {
        importData(aReply->readAll());
    }
}

void ImportScheduleWidget::downloadSchedule()
{
    qDebug() << "downloading schedule";

    QNetworkRequest request;
    request.setUrl(QUrl(SCHEDULE_URL));
    mNetworkAccessManager->get(request);
}

void ImportScheduleWidget::importData(const QByteArray &aData)
{
    browse->hide();
    online->hide();
    progressBar->show();

    int confId = mXmlParser->parseData(aData);

    progressBar->hide();
    browse->show();
    online->show();
    importScheduleLabel->setText("Import schedule: ");

    emit(scheduleImported(confId));
}


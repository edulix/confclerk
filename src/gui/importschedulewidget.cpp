#include "importschedulewidget.h"

#include <schedulexmlparser.h>
#include <sqlengine.h>

#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QDebug>

ImportScheduleWidget::ImportScheduleWidget(QWidget *aParent)
    : QWidget(aParent)
    , mSqlEngine(NULL)
{
    setupUi(this);

    mXmlParser = new ScheduleXmlParser(this);
    connect(mXmlParser, SIGNAL(progressStatus(int)), SLOT(showParsingProgress(int)));
    connect(mXmlParser, SIGNAL(parsingSchedule(const QString &)), SLOT(parsingSchedule(const QString &)));

    connect(browse, SIGNAL(clicked()), SLOT(browseSchedule()));
    progressBar->hide();
}

ImportScheduleWidget::~ImportScheduleWidget()
{
    if(mXmlParser)
    {
        delete mXmlParser;
        mXmlParser = NULL;
    }
}

void ImportScheduleWidget::setSqlEngine(SqlEngine *aSqlEngine)
{
    Q_ASSERT(aSqlEngine != NULL);

    mSqlEngine = aSqlEngine;
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
    Q_ASSERT(mSqlEngine != NULL);

    QString scheduleFileName = QFileDialog::getOpenFileName(this, tr("Select Conference Schedule"), QDir::homePath(), tr("Schedule Files (*.xml)"));
    if(QFile::exists(scheduleFileName))
    {
        QFile file(scheduleFileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "can't open " << file.fileName();
            return;
        }

        QByteArray data = file.readAll();
        browse->hide();
        progressBar->show();
        int confId = mXmlParser->parseData(data,mSqlEngine);

        progressBar->hide();
        browse->show();
        importScheduleLabel->setText("Import schedule: ");

        emit(scheduleImported(confId));
    }
    else
    {
        progressBar->hide();
    }
}


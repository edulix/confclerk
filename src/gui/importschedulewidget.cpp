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
    connect(mXmlParser, SIGNAL(parsingSchedule(const QString &)), SLOT(setWindowTitle(const QString &)));

    connect(import, SIGNAL(clicked()), SLOT(importSchedule()));
    connect(search, SIGNAL(clicked()), SLOT(searchSchedule()));
    progressBar->hide();
    import->setEnabled(false);
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

void ImportScheduleWidget::showParsingProgress(int progress)
{
    progressBar->setValue(progress);
}

void ImportScheduleWidget::searchSchedule()
{
    Q_ASSERT(mSqlEngine != NULL);

    mScheduleFileName = QFileDialog::getOpenFileName(this, tr("Select Conference Schedule"), QDir::homePath(), tr("Schedule Files (*.xml)"));
    if(QFile::exists(mScheduleFileName))
        import->setEnabled(true);
    else
    {
        import->setEnabled(false);
        progressBar->hide();
    }
}

void ImportScheduleWidget::importSchedule()
{
    if(!mSqlEngine)
    {
        qDebug() << "ImportScheduleWidget::importSchedule(): sqlEngine not set";
        return;
    }

    QFile file(mScheduleFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "can't open " << file.fileName();
        return;
    }

    QByteArray data = file.readAll();
    progressBar->show();
    int confId = mXmlParser->parseData(data,mSqlEngine);

    // hide stuff
    import->setEnabled(false);
    progressBar->hide();

    emit(scheduleImported(confId));
}


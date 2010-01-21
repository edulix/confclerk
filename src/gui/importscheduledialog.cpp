#include "importscheduledialog.h"

#include <schedulexmlparser.h>
#include <sqlengine.h>

#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QDebug>

ImportScheduleDialog::ImportScheduleDialog(SqlEngine *aSqlEngine, QWidget *aParent)
    : QDialog(aParent)
    , mSqlEngine(aSqlEngine)
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

ImportScheduleDialog::~ImportScheduleDialog()
{
    if(mXmlParser)
    {
        delete mXmlParser;
        mXmlParser = NULL;
    }
}

void ImportScheduleDialog::showParsingProgress(int progress)
{
    progressBar->setValue(progress);
}

void ImportScheduleDialog::searchSchedule()
{
    mScheduleFileName = QFileDialog::getOpenFileName(this, tr("Select Conference Schedule"), QDir::homePath(), tr("Schedule Files (*.xml)"));
    if(QFile::exists(mScheduleFileName))
        import->setEnabled(true);
    else
    {
        import->setEnabled(false);
        progressBar->hide();
    }
}

void ImportScheduleDialog::importSchedule()
{
    QFile file(mScheduleFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "can't open " << file.fileName();
        return;
    }

    QByteArray data = file.readAll();
    if(mSqlEngine)
    {
        progressBar->show();
        mXmlParser->parseData(data,mSqlEngine);
        close();
    }
}


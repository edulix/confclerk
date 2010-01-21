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
    connect(mXmlParser, SIGNAL(progressStatus(int)), this, SLOT(showParsingProgress(int)));
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
    fileName->setText(mScheduleFileName);
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
    }
}


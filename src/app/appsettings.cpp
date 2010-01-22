#include "appsettings.h"

const QString CONF_ID_SETTING ("confId"); 

QSettings AppSettings::mSettings("Ixonos", "FOSDEM");

AppSettings::AppSettings()
{ }

int AppSettings::confId()
{
    return mSettings.value(CONF_ID_SETTING).toInt();
}

void AppSettings::setConfId(int aConfId)
{
    mSettings.setValue(CONF_ID_SETTING, aConfId);
}


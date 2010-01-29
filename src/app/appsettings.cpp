#include "appsettings.h"

const QString PROXY_ADDRESS_SETTING ("proxyAddress"); 
const QString PROXY_PORT_SETTING ("proxyPort"); 
const QString PROXY_ISDIRECT_SETTING ("proxyIsDirectConnection"); 

QSettings AppSettings::mSettings("Ixonos", "FOSDEM");

QString AppSettings::proxyAddress()
{
    return mSettings.value(PROXY_ADDRESS_SETTING).toString();
}

quint16 AppSettings::proxyPort()
{
    return mSettings.value(PROXY_PORT_SETTING).toUInt();
}

bool AppSettings::isDirectConnection()
{
    return mSettings.value(PROXY_ISDIRECT_SETTING).toBool();
}

void AppSettings::setProxyAddress(const QString &aAddress)
{
    mSettings.setValue(PROXY_ADDRESS_SETTING, aAddress);
}

void AppSettings::setProxyPort(const quint16 aPort)
{
    mSettings.setValue(PROXY_PORT_SETTING, aPort);
}

void AppSettings::setDirectConnection(bool aDirectConnection)
{
    mSettings.setValue(PROXY_ISDIRECT_SETTING, aDirectConnection);
}

bool AppSettings::contains(const QString &aKey)
{
    return mSettings.contains(aKey);
}


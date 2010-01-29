
#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>
#include <QSettings>

class AppSettings
{
    private:
        AppSettings() {}
        static QSettings mSettings;

    public:
        static bool contains(const QString &aKey);

        static QString proxyAddress();
        static quint16 proxyPort();
        static bool isDirectConnection();

        static void setProxyAddress(const QString &aAddress);
        static void setProxyPort(const quint16 aPort);
        static void setDirectConnection(bool aDirectConnection);
};

#endif /* APPSETTINGS_H */


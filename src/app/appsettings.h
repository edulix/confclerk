
#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>
#include <QSettings>

class AppSettings
{
    private:
        AppSettings();
        static QSettings mSettings;

    public:
        static int confId(); // conference Id
        static void setConfId(int aConfId);
};

#endif /* APPSETTINGS_H */


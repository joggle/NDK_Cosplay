#ifndef NDK_COSTUME_CONTEST_DBSETTINGS_H
#define NDK_COSTUME_CONTEST_DBSETTINGS_H

#include <QString>

// singleton class used to store database connection settings
class DBSettings
{
public:
    static DBSettings* instance();
    static void cleanup();
    ~DBSettings();

    QString dbHost;
    int     dbPort;
    QString dbName;
    QString userName;
    QString password;
private:
    DBSettings();
    DBSettings(const DBSettings& /*other*/) {}
    DBSettings& operator= (const DBSettings& /*other*/) {return *this;}

    static DBSettings* instance_;
};

#endif // NDK_COSTUME_CONTEST_DBSETTINGS_H

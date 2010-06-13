#include "DBSettings.h"

DBSettings* DBSettings::instance_=0;

DBSettings::DBSettings()
          : dbHost(),
            dbPort(5432),
            dbName("ndk_cosplay"),
            userName(),
            password()
{
}

DBSettings::~DBSettings()
{
}

DBSettings*
DBSettings::instance()
{
    if (instance_ == 0)
    {
        instance_ = new DBSettings();
    }
    return instance_;
}

void
DBSettings::cleanup()
{
    delete instance_;
    instance_=0;
}


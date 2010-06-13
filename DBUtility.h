#ifndef NDK_COSTUME_CONTEST_DBUTILITY_H
#define NDK_COSTUME_CONTEST_DBUTILITY_H

#include <QString>

class DBUtility
{
public:
    static QString quote(QString value) { value.replace("'","''"); return value; }
};

#endif // NDK_COSTUME_CONTEST_DBUTILITY_H

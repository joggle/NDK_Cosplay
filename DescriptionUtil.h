#ifndef NDK_COSTUME_CONTEST_DESCRIPTION_UTIL_H
#define NDK_COSTUME_CONTEST_DESCRIPTION_UTIL_H

#include <QString>

class DescriptionUtil
{
public:
    static QString getDescriptionSingle(const QString& player, const QString& character, const QString& origin);
    static QString getDescriptionSkit(const QString& groupName, const QString& skitName);
};

#endif // NDK_COSTUME_CONTEST_DESCRIPTION_UTIL_H

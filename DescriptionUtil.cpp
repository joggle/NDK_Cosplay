#include "DescriptionUtil.h"

QString
DescriptionUtil::getDescriptionSingle(const QString& player, const QString& character, const QString& origin)
{
    QString retVal;
    if (!player.isEmpty())
        retVal = player;
    if (!character.isEmpty())
    {
        if (!retVal.isEmpty())
            retVal.append(" as ");
        retVal.append(character);
    }
    if (!origin.isEmpty())
    {
        if (!retVal.isEmpty())
            retVal.append(" from ");
        retVal.append(origin);
    }
    return retVal;
}

QString
DescriptionUtil::getDescriptionSkit(const QString& groupName, const QString& skitName)
{
    QString retVal;
    if (!groupName.isEmpty())
        retVal = groupName;
    if (!skitName.isEmpty())
    {
        if (!retVal.isEmpty())
            retVal.append(" preforming ");
        retVal.append(skitName);
    }
    return retVal;
}


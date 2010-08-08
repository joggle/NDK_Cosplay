#include <QtGui>
#include <QtSql>

#include "DialogNewEntry.h"
#include "DBUtility.h"
#include "DescriptionUtil.h"

DialogNewEntry::DialogNewEntry(QWidget* parent)
              : QDialog(parent)
{
    QVBoxLayout* containerLayout = new QVBoxLayout();
    QWidget* containerWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(new QLabel("Information from web form:"));
    webFormInfo = new QTextEdit();
    mainLayout->addWidget(webFormInfo);
    QHBoxLayout* webButtonLayout = new QHBoxLayout();
    autoFill = new QPushButton("Auto-fill fields");
    connect(autoFill,SIGNAL(clicked()),this,SLOT(autoFillFields()));
    clearData = new QPushButton("Clear fields");
    connect(clearData,SIGNAL(clicked()),this,SLOT(clearDataFields()));
    QPushButton* updateDesc = new QPushButton("Update description");
    connect(updateDesc,SIGNAL(clicked()),this,SLOT(updateDescription()));
    updateDesc->setToolTip("Update description using current data for this entry");
    webButtonLayout->addWidget(autoFill);
    webButtonLayout->addWidget(clearData);
    webButtonLayout->addWidget(updateDesc);
    mainLayout->addLayout(webButtonLayout);
    QFormLayout* mainFormLayout = new QFormLayout();
    entryDescription = new QLineEdit();
    mainFormLayout->addRow("Description:",entryDescription);
    groupName = new QLineEdit();
    mainFormLayout->addRow("Group name:",groupName);
    skitName = new QLineEdit();
    mainFormLayout->addRow("Skit name:",skitName);
    groupEMail = new QLineEdit();
    mainFormLayout->addRow("Group e-mail:",groupEMail);
    QButtonGroup* categoryGroup = new QButtonGroup();
    catNotSet       = new QRadioButton("Not set");
    catSkit         = new QRadioButton("Skit");
    catBeginner     = new QRadioButton("Beginner");
    catIntermediate = new QRadioButton("Intermediate");
    catMaster       = new QRadioButton("Master");
    catChildren     = new QRadioButton("Children");
    QHBoxLayout* catLayout = new QHBoxLayout();
    catLayout->addWidget(catNotSet);
    catLayout->addWidget(catSkit);
    catLayout->addWidget(catBeginner);
    catLayout->addWidget(catIntermediate);
    catLayout->addWidget(catMaster);
    catLayout->addWidget(catChildren);
    catLayout->addStretch();
    categoryGroup->addButton(catNotSet);
    categoryGroup->addButton(catSkit);
    categoryGroup->addButton(catBeginner);
    categoryGroup->addButton(catIntermediate);
    categoryGroup->addButton(catMaster);
    categoryGroup->addButton(catChildren);
    catNotSet->setChecked(true);
    mainFormLayout->addRow("Category:",catLayout);
    craftmanship = new QCheckBox();
    mainFormLayout->addRow("Craftmanship?",craftmanship);

    int ii;
    playerName = new QLineEdit*[6];
    playerCharacter = new QLineEdit*[6];
    playerOrigin = new QLineEdit*[6];
    playerDescription = new QLineEdit*[6];
    playerDescBtn = new QPushButton*[6];
    for (ii=0; ii < 6; ++ii)
    {
        playerName[ii] = new QLineEdit();
        playerCharacter[ii] = new QLineEdit();
        playerOrigin[ii] = new QLineEdit();
        playerDescription[ii] = new QLineEdit();
        playerDescBtn[ii] = new QPushButton("Update description");
        playerDescBtn[ii]->setProperty("player_index",ii+1);
        connect(playerDescBtn[ii],SIGNAL(clicked()),this,SLOT(handlePlayerDescBtn()));
    }

    for (ii=1; ii <= 6; ++ii)
        addPlayerLayout(ii,mainFormLayout);
    scriptUrl = new QLineEdit();
    mainFormLayout->addRow("Script URL:",scriptUrl);
    musicUrl = new QLineEdit();
    mainFormLayout->addRow("Music URL:",musicUrl);
    mainLayout->addLayout(mainFormLayout);
    mainLayout->addWidget(new QLabel("Entry comments:"));
    entryComments = new QTextEdit();
    mainLayout->addWidget(entryComments);
    mainLayout->addWidget(new QLabel("Announcer notes:"));
    announcerNotes = new QTextEdit();
    announcerNotes->setMaximumHeight(50);
    mainLayout->addWidget(announcerNotes);
    mainLayout->addWidget(new QLabel("Sound notes:"));
    soundNotes = new QTextEdit();
    soundNotes->setMaximumHeight(50);
    mainLayout->addWidget(soundNotes);
    containerWidget->setLayout(mainLayout);
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidget(containerWidget);
    containerLayout->addWidget(scrollArea);
    QDialogButtonBox* buttonBox = new QDialogButtonBox();
    buttonBox->addButton(QDialogButtonBox::Save);
    buttonBox->addButton(QDialogButtonBox::Cancel);
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
    connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
    containerLayout->addWidget(buttonBox);
    setLayout(containerLayout);
    setWindowIcon(QIcon(":/images/new_entry.png"));
    setWindowTitle("Add new entry");
    loadSettings();
}

DialogNewEntry::~DialogNewEntry()
{
}

void
DialogNewEntry::handlePlayerDescBtn()
{
    updatePlayerDescription(sender()->property("player_index").toInt());
}

void
DialogNewEntry::addPlayerLayout(int playerID, QFormLayout* mainLayout)
{
    QVBoxLayout* playerLayout = new QVBoxLayout();
    QHBoxLayout* playerTopLayout = new QHBoxLayout();
    QHBoxLayout* playerBottomLayout = new QHBoxLayout();
    playerTopLayout->addWidget(new QLabel("Name:"));
    playerTopLayout->addWidget(playerName[playerID-1]);
    playerTopLayout->addWidget(new QLabel("Character:"));
    playerTopLayout->addWidget(playerCharacter[playerID-1]);
    playerTopLayout->addWidget(new QLabel("Origin:"));
    playerTopLayout->addWidget(playerOrigin[playerID-1]);
    playerLayout->addLayout(playerTopLayout);
    playerBottomLayout->addWidget(new QLabel("Description:"));
    playerBottomLayout->addWidget(playerDescription[playerID-1]);
    playerBottomLayout->addWidget(playerDescBtn[playerID-1]);
    playerLayout->addLayout(playerBottomLayout);
    mainLayout->addRow(QString("Contestant %1:").arg(playerID),playerLayout);
}

void
DialogNewEntry::accept()
{
    // store data in database
    QString sqlString;
    QSqlDatabase db(QSqlDatabase::database());
    if (!db.transaction())
    {
		QMessageBox::critical(this,"Unable to start transaction",QString("Unable to start database transaction. Error: %1").arg(db.lastError().text()));
        return;
    }
    // insert each contestant
    QString errStr;
    int playerID[6];
    int ii;
    for (ii=0; ii < 6; ++ii)
    {
        playerID[ii] = -1;
        if (!playerName[ii]->text().isEmpty())
        {
            if (!addPlayer(playerName[ii]->text(),playerCharacter[ii]->text(),playerOrigin[ii]->text(),playerDescription[ii]->text(),playerID[ii],errStr))
            {
    		    QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant %1. Error: %2").arg(ii+1).arg(errStr));
                db.rollback();
                return;
            }
        } else if (ii==0)
        {
		    QMessageBox::critical(this,"Contestant 1 not set!","Contestant 1 must be set. Can't have an entry with no performer!");
            db.rollback();
            return;
        }
    }
    // get next order number
    QSqlQuery orderQuery;
    int order=-1;
    if (orderQuery.exec("SELECT MAX(\"order\") AS max_order FROM active_entries"))
    {
        order=1;
        if (orderQuery.next())
        {
            int orderIndex = orderQuery.record().indexOf("max_order");
            order = orderQuery.value(orderIndex).toInt();
            order++;
        }
    }
    if (order < 1)
    {
        QMessageBox::critical(this,"Unable to get next order",QString("Unable to get next entry order. Error: %1").arg(orderQuery.lastError().text()));
        db.rollback();
        return;
    }
    sqlString = "INSERT INTO entry (description, group_name, register_date, category_id, craft_judged, player_1_id";
    QString entryStr = entryComments->toPlainText();
    QString announcerStr = announcerNotes->toPlainText();
    QString soundStr = soundNotes->toPlainText();
    for (ii=1; ii < 6; ++ii)
    {
        if (playerID[ii] != -1)
            sqlString.append(QString(", player_%1_id").arg(ii+1));
    }
    if (!groupEMail->text().isEmpty())
        sqlString.append(", contact_email");
    if (!entryStr.isEmpty())
        sqlString.append(", notes_entry");
    if (!announcerStr.isEmpty())
        sqlString.append(", notes_announcer");
    if (!soundStr.isEmpty())
        sqlString.append(", notes_sound");
    if (!scriptUrl->text().isEmpty())
        sqlString.append(", script_url");
    if (!skitName->text().isEmpty())
        sqlString.append(", skit_name");
    if (!musicUrl->text().isEmpty())
        sqlString.append(", music_url");
    sqlString.append(") VALUES (");
    int catID=getCategoryID();
    QString craftJudged = (craftmanship->isChecked() ? "true" : "false");
    sqlString.append(QString("'%1', '%2', now(), '%3', %4, %5")
                    //.arg(order)
                    .arg(DBUtility::quote(entryDescription->text()))
                    .arg(DBUtility::quote(groupName->text()))
                    .arg(catID)
                    .arg(craftJudged)
                    .arg(playerID[0]));
    for (ii=1; ii < 6; ++ii)
    {
        if (playerID[ii] != -1)
            sqlString.append(QString(", %1").arg(playerID[ii]));
    }
    if (!groupEMail->text().isEmpty())
        sqlString.append(QString(", '%1'").arg(DBUtility::quote(groupEMail->text())));
    if (!entryStr.isEmpty())
        sqlString.append(QString(", '%1'").arg(DBUtility::quote(entryStr)));
    if (!announcerStr.isEmpty())
        sqlString.append(QString(", '%1'").arg(DBUtility::quote(announcerStr)));
    if (!soundStr.isEmpty())
        sqlString.append(QString(", '%1'").arg(DBUtility::quote(soundStr)));
    if (!scriptUrl->text().isEmpty())
        sqlString.append(QString(", '%1'").arg(DBUtility::quote(scriptUrl->text())));
    if (!skitName->text().isEmpty())
        sqlString.append(QString(", '%1'").arg(DBUtility::quote(skitName->text())));
    if (!musicUrl->text().isEmpty())
        sqlString.append(QString(", '%1'").arg(DBUtility::quote(musicUrl->text())));
    sqlString.append(") RETURNING id_entry");
    qDebug("Trying to execute query: [[%s]]",qPrintable(sqlString));
    QSqlQuery addEntryQuery;
    if (!addEntryQuery.exec(sqlString))
    {
        QMessageBox::critical(this,"Unable to add entry",QString("Unable to add entry to database. Error: %1").arg(addEntryQuery.lastError().text()));
        db.rollback();
        return;
    }
    int entryID=0;
    if (addEntryQuery.next())
    {
        int fieldNo = addEntryQuery.record().indexOf("id_entry");
        entryID = addEntryQuery.value(fieldNo).toInt();
    } else
    {
        QMessageBox::critical(this,"Unable to add entry","Unable to add entry to database because query adding entry didn't return its ID");
        db.rollback();
        return;
    }
    // add the entry to the list of active entries
    QSqlQuery addActiveEntryQuery;
    QString sqlActiveEntry(QString("INSERT INTO active_entries (entry_id, \"order\") VALUES (%1, %2)")
        .arg(entryID)
        .arg(order));
    if (!addActiveEntryQuery.exec(sqlActiveEntry))
    {
        QMessageBox::critical(this,"Unable to add entry",QString("Unable to add active entry to database. Error: %1").arg(addActiveEntryQuery.lastError().text()));
        db.rollback();
        return;
    }
    if (!db.commit())
    {
		QMessageBox::critical(this,"Unable to save",QString("Unable to coomit to NDK costume contest database. Error: %1").arg(db.lastError().text()));
        return;
    }
    // end of saving data in database

    saveSettings();
    QDialog::accept();
}

int
DialogNewEntry::getCategoryID()
{
    QString catName;
    if (catBeginner->isChecked())
    {
        catName="beginner";
    } else if (catIntermediate->isChecked())
    {
        catName="intermediate";
    } else if (catMaster->isChecked())
    {
        catName="master";
    } else if (catSkit->isChecked())
    {
        catName="skits";
    } else if (catChildren->isChecked())
    {
        catName="children";
    } else
    {
        catName = "not set";
    }
    QSqlQuery catQuery;
    int catID=5;
    if (catQuery.exec(QString("SELECT category_id FROM category where name='%1'").arg(catName)))
    {
        if (catQuery.next())
        {
            int catIndex = catQuery.record().indexOf("category_id");
            catID = catQuery.value(catIndex).toInt();
        }
    }
    return catID;
}

bool
DialogNewEntry::addPlayer(QString name, QString character, QString origin,
                          QString desc, int& playerID, QString& errStr)
{
    QString sqlString;
    sqlString = "INSERT INTO performer (real_name";
    if (!character.isEmpty())
        sqlString.append(", character_name");
    if (!origin.isEmpty())
        sqlString.append(", origin");
    if (!desc.isEmpty())
        sqlString.append(", description");
    sqlString.append(") VALUES ('");
    sqlString.append(DBUtility::quote(name));
    sqlString.append("'");
    if (!character.isEmpty())
    {
        sqlString.append(", '");
        sqlString.append(DBUtility::quote(character));
        sqlString.append("'");
    }
    if (!origin.isEmpty())
    {
        sqlString.append(", '");
        sqlString.append(DBUtility::quote(origin));
        sqlString.append("'");
    }
    if (!desc.isEmpty())
    {
        sqlString.append(", '");
        sqlString.append(DBUtility::quote(desc));
        sqlString.append("'");
    }
    sqlString.append(") RETURNING id_player");
    QSqlQuery query;
    if (query.exec(sqlString))
    {
        if (query.next())
        {
            int fieldNo = query.record().indexOf("id_player");
            playerID = query.value(fieldNo).toInt();
            //QMessageBox::information(this,"Added ID",QString("Added ID %1").arg(id_player));
        }
        return true;
    } else
    {
        errStr = query.lastError().text();
        return false;
    }
    return false; // tmp!!
}

void
DialogNewEntry::reject()
{
    saveSettings();
    QDialog::reject();
}

void
DialogNewEntry::loadSettings()
{
    QSettings settings;
    settings.beginGroup("NewEntryDialog");
    resize(settings.value("size",QSize(520,671)).toSize());
    move(settings.value("pos",QPoint(200,200)).toPoint());
    settings.endGroup();
}

void
DialogNewEntry::saveSettings()
{
    QSettings settings;
    settings.beginGroup("NewEntryDialog");
    settings.setValue("size",size());
    settings.setValue("pos",pos());
    settings.endGroup();
}

void
DialogNewEntry::autoFillFields()
{
    QString formText = webFormInfo->toPlainText();
    QRegExp rxGroupName("Group Name: ([^\\n]+)");
    int pos = rxGroupName.indexIn(formText);
    bool somethingSet=false;
    if (pos > -1)
    {
        groupName->setText(rxGroupName.cap(1));
        somethingSet=true;
    }
    QRegExp rxGroupEMail("Group E-mail Address: ([^\\n]+)");
    pos = rxGroupEMail.indexIn(formText);
    if (pos > -1)
    {
        groupEMail->setText(rxGroupEMail.cap(1));
        somethingSet=true;
    }
    QRegExp rxCraftmanship("Would you like craftsmanship judging\\?: Yes");//: Yes");
    pos = rxCraftmanship.indexIn(formText);
    if (pos > -1)
        craftmanship->setChecked(true);
    else
        craftmanship->setChecked(false);
    QRegExp rxCompLevel("Competition Level: ([^\\n]+)");
    pos = rxCompLevel.indexIn(formText);
    if (pos > -1)
    {
        QString complevel = rxCompLevel.cap(1);
        if (complevel == "Beginner")
            catBeginner->setChecked(true);
        else if (complevel == "Intermediate")
            catIntermediate->setChecked(true);
        else if (complevel == "Master")
            catMaster->setChecked(true);
        somethingSet=true;
    }
    // see if this is a skit
    QRegExp rxSkitTitle("Skit Title: ([^\\n]+)");
    pos = rxSkitTitle.indexIn(formText);
    if (pos > -1)
    {
        catSkit->setChecked(true);
        skitName->setText(rxSkitTitle.cap(1));
    } else
        skitName->setText("");
    int iPlayer;
    for (iPlayer=1; iPlayer <= 6; ++iPlayer)
    {
        QRegExp rxContestant(QString("Contestant #%1's Name: ([^\\n]+)").arg(iPlayer));
        pos = rxContestant.indexIn(formText);
        if (pos > -1)
        {
            playerName[iPlayer-1]->setText(rxContestant.cap(1));
            somethingSet=true;
        }
        QRegExp rxCharacter(QString("Contestant #%1's Character: ([^\\n]+)").arg(iPlayer));
        pos = rxCharacter.indexIn(formText);
        if (pos > -1)
        {
            playerCharacter[iPlayer-1]->setText(rxCharacter.cap(1));
            somethingSet=true;
        }
        QRegExp rxSource(QString("Contestant #%1's Source: ([^\\n]+)").arg(iPlayer));
        pos = rxSource.indexIn(formText);
        if (pos > -1)
        {
            playerOrigin[iPlayer-1]->setText(rxSource.cap(1));
            somethingSet=true;
        }
    } // for each player
    QRegExp rxScript("Script: ([^\\n]+)");
    pos = rxScript.indexIn(formText);
    if (pos > -1)
    {
        scriptUrl->setText(rxScript.cap(1));
        somethingSet=true;
    } else
        scriptUrl->setText("");
    QRegExp rxMusic("Music: ([^\\n]+)");
    pos = rxMusic.indexIn(formText);
    if (pos > -1)
    {
        musicUrl->setText(rxMusic.cap(1));
        somethingSet=true;
    } else
        musicUrl->setText("");
    QRegExp rxComments("Comments:(\\s*)(.+)");
    pos = rxComments.indexIn(formText);
    if (pos > -1)
    {
        entryComments->setText(rxComments.cap(2));
        somethingSet=true;
    }
    if (!somethingSet)
    {
        QMessageBox::warning(this,"Unable to parse data","Unable to parse any data from web form text!");
    } else
    {
        // update the entry's description
        updateDescription();
    }
}

void
DialogNewEntry::updateDescription()
{
    if (catSkit->isChecked())
    {
        entryDescription->setText(DescriptionUtil::getDescriptionSkit(groupName->text(),skitName->text()));
    } else if (catNotSet->isChecked())
    {
        if (!skitName->text().isEmpty())
            entryDescription->setText(DescriptionUtil::getDescriptionSkit(groupName->text(),skitName->text()));
        else
            entryDescription->setText(DescriptionUtil::getDescriptionSingle(playerName[0]->text(),playerCharacter[0]->text(),playerOrigin[0]->text()));
    } else
    {
        entryDescription->setText(DescriptionUtil::getDescriptionSingle(playerName[0]->text(),playerCharacter[0]->text(),playerOrigin[0]->text()));
    }
    for (int ii=1; ii <= 6; ++ii)
        updatePlayerDescription(ii);
}

void
DialogNewEntry::updatePlayerDescription(int playerIndex)
{
    playerDescription[playerIndex-1]->setText(DescriptionUtil::getDescriptionSingle(playerName[playerIndex-1]->text(),playerCharacter[playerIndex-1]->text(),playerOrigin[playerIndex-1]->text()));
}

void
DialogNewEntry::clearDataFields()
{
    webFormInfo->setText("");
    entryDescription->setText("");
    groupName->setText("");
    skitName->setText("");
    groupEMail->setText("");
    scriptUrl->setText("");
    craftmanship->setChecked(false);
    catNotSet->setChecked(true);
    entryComments->setText("");
    announcerNotes->setText("");
    soundNotes->setText("");
    for (int ii=0; ii < 6; ++ii)
    {
        playerName[ii]->setText("");
        playerCharacter[ii]->setText("");
        playerOrigin[ii]->setText("");
        playerDescription[ii]->setText("");
    }
}

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
    QHBoxLayout* catLayout = new QHBoxLayout();
    catLayout->addWidget(catNotSet);
    catLayout->addWidget(catSkit);
    catLayout->addWidget(catBeginner);
    catLayout->addWidget(catIntermediate);
    catLayout->addWidget(catMaster);
    catLayout->addStretch();
    categoryGroup->addButton(catNotSet);
    categoryGroup->addButton(catSkit);
    categoryGroup->addButton(catBeginner);
    categoryGroup->addButton(catIntermediate);
    categoryGroup->addButton(catMaster);
    catNotSet->setChecked(true);
    mainFormLayout->addRow("Category:",catLayout);
    craftmanship = new QCheckBox();
    mainFormLayout->addRow("Craftmanship?",craftmanship);

    QVBoxLayout* player1Layout = new QVBoxLayout();
    QHBoxLayout* player1TopLayout = new QHBoxLayout();
    QHBoxLayout* player1BottomLayout = new QHBoxLayout();
    player1TopLayout->addWidget(new QLabel("Name:"));
    player1Name = new QLineEdit();
    player1TopLayout->addWidget(player1Name);
    player1TopLayout->addWidget(new QLabel("Character:"));
    player1Character = new QLineEdit();
    player1TopLayout->addWidget(player1Character);
    player1TopLayout->addWidget(new QLabel("Origin:"));
    player1Origin = new QLineEdit();
    player1TopLayout->addWidget(player1Origin);
    player1Layout->addLayout(player1TopLayout);
    player1BottomLayout->addWidget(new QLabel("Description:"));
    player1Description = new QLineEdit();
    player1BottomLayout->addWidget(player1Description);
    player1DescBtn = new QPushButton("Update description");
    player1BottomLayout->addWidget(player1DescBtn);
    connect(player1DescBtn,SIGNAL(clicked()),this,SLOT(updatePlayer1Desc()));
    player1Layout->addLayout(player1BottomLayout);
    mainFormLayout->addRow("Contestant 1:",player1Layout);

    QVBoxLayout* player2Layout = new QVBoxLayout();
    QHBoxLayout* player2TopLayout = new QHBoxLayout();
    QHBoxLayout* player2BottomLayout = new QHBoxLayout();
    player2TopLayout->addWidget(new QLabel("Name:"));
    player2Name = new QLineEdit();
    player2TopLayout->addWidget(player2Name);
    player2TopLayout->addWidget(new QLabel("Character:"));
    player2Character = new QLineEdit();
    player2TopLayout->addWidget(player2Character);
    player2TopLayout->addWidget(new QLabel("Origin:"));
    player2Origin = new QLineEdit();
    player2TopLayout->addWidget(player2Origin);
    player2Layout->addLayout(player2TopLayout);
    player2BottomLayout->addWidget(new QLabel("Description:"));
    player2Description = new QLineEdit();
    player2BottomLayout->addWidget(player2Description);
    player2DescBtn = new QPushButton("Update description");
    player2BottomLayout->addWidget(player2DescBtn);
    connect(player2DescBtn,SIGNAL(clicked()),this,SLOT(updatePlayer2Desc()));
    player2Layout->addLayout(player2BottomLayout);
    mainFormLayout->addRow("Contestant 2:",player2Layout);

    QVBoxLayout* player3Layout = new QVBoxLayout();
    QHBoxLayout* player3TopLayout = new QHBoxLayout();
    QHBoxLayout* player3BottomLayout = new QHBoxLayout();
    player3TopLayout->addWidget(new QLabel("Name:"));
    player3Name = new QLineEdit();
    player3TopLayout->addWidget(player3Name);
    player3TopLayout->addWidget(new QLabel("Character:"));
    player3Character = new QLineEdit();
    player3TopLayout->addWidget(player3Character);
    player3TopLayout->addWidget(new QLabel("Origin:"));
    player3Origin = new QLineEdit();
    player3TopLayout->addWidget(player3Origin);
    player3Layout->addLayout(player3TopLayout);
    player3BottomLayout->addWidget(new QLabel("Description:"));
    player3Description = new QLineEdit();
    player3BottomLayout->addWidget(player3Description);
    player3DescBtn = new QPushButton("Update description");
    player3BottomLayout->addWidget(player3DescBtn);
    connect(player3DescBtn,SIGNAL(clicked()),this,SLOT(updatePlayer3Desc()));
    player3Layout->addLayout(player3BottomLayout);
    mainFormLayout->addRow("Contestant 3:",player3Layout);

    QVBoxLayout* player4Layout = new QVBoxLayout();
    QHBoxLayout* player4TopLayout = new QHBoxLayout();
    QHBoxLayout* player4BottomLayout = new QHBoxLayout();
    player4TopLayout->addWidget(new QLabel("Name:"));
    player4Name = new QLineEdit();
    player4TopLayout->addWidget(player4Name);
    player4TopLayout->addWidget(new QLabel("Character:"));
    player4Character = new QLineEdit();
    player4TopLayout->addWidget(player4Character);
    player4TopLayout->addWidget(new QLabel("Origin:"));
    player4Origin = new QLineEdit();
    player4TopLayout->addWidget(player4Origin);
    player4Layout->addLayout(player4TopLayout);
    player4BottomLayout->addWidget(new QLabel("Description:"));
    player4Description = new QLineEdit();
    player4BottomLayout->addWidget(player4Description);
    player4DescBtn = new QPushButton("Update description");
    player4BottomLayout->addWidget(player4DescBtn);
    connect(player4DescBtn,SIGNAL(clicked()),this,SLOT(updatePlayer4Desc()));
    player4Layout->addLayout(player4BottomLayout);
    mainFormLayout->addRow("Contestant 4:",player4Layout);

    QVBoxLayout* player5Layout = new QVBoxLayout();
    QHBoxLayout* player5TopLayout = new QHBoxLayout();
    QHBoxLayout* player5BottomLayout = new QHBoxLayout();
    player5TopLayout->addWidget(new QLabel("Name:"));
    player5Name = new QLineEdit();
    player5TopLayout->addWidget(player5Name);
    player5TopLayout->addWidget(new QLabel("Character:"));
    player5Character = new QLineEdit();
    player5TopLayout->addWidget(player5Character);
    player5TopLayout->addWidget(new QLabel("Origin:"));
    player5Origin = new QLineEdit();
    player5TopLayout->addWidget(player5Origin);
    player5Layout->addLayout(player5TopLayout);
    player5BottomLayout->addWidget(new QLabel("Description:"));
    player5Description = new QLineEdit();
    player5BottomLayout->addWidget(player5Description);
    player5DescBtn = new QPushButton("Update description");
    player5BottomLayout->addWidget(player5DescBtn);
    connect(player5DescBtn,SIGNAL(clicked()),this,SLOT(updatePlayer5Desc()));
    player5Layout->addLayout(player5BottomLayout);
    mainFormLayout->addRow("Contestant 5:",player5Layout);

    QVBoxLayout* player6Layout = new QVBoxLayout();
    QHBoxLayout* player6TopLayout = new QHBoxLayout();
    QHBoxLayout* player6BottomLayout = new QHBoxLayout();
    player6TopLayout->addWidget(new QLabel("Name:"));
    player6Name = new QLineEdit();
    player6TopLayout->addWidget(player6Name);
    player6TopLayout->addWidget(new QLabel("Character:"));
    player6Character = new QLineEdit();
    player6TopLayout->addWidget(player6Character);
    player6TopLayout->addWidget(new QLabel("Origin:"));
    player6Origin = new QLineEdit();
    player6TopLayout->addWidget(player6Origin);
    player6Layout->addLayout(player6TopLayout);
    player6BottomLayout->addWidget(new QLabel("Description:"));
    player6Description = new QLineEdit();
    player6BottomLayout->addWidget(player6Description);
    player6DescBtn = new QPushButton("Update description");
    player6BottomLayout->addWidget(player6DescBtn);
    connect(player6DescBtn,SIGNAL(clicked()),this,SLOT(updatePlayer6Desc()));
    player6Layout->addLayout(player6BottomLayout);
    mainFormLayout->addRow("Contestant 6:",player6Layout);
    scriptUrl = new QLineEdit();
    mainFormLayout->addRow("Script URL:",scriptUrl);
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
    int playerID1, playerID2, playerID3, playerID4, playerID5, playerID6;
    playerID1=playerID2=playerID3=playerID4=playerID5=playerID6=-1;
    if (!player1Name->text().isEmpty())
    {
        if (!addPlayer(player1Name->text(),player1Character->text(),player1Origin->text(),player1Description->text(),playerID1,errStr))
        {
    		QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant 1. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    } else
    {
		QMessageBox::critical(this,"Contestant 1 not set!","Contestant 1 must be set. Can't have an entry with no performer!");
        db.rollback();
        return;
    }
    if (!player2Name->text().isEmpty())
    {
        if (!addPlayer(player2Name->text(),player2Character->text(),player2Origin->text(),player2Description->text(),playerID2,errStr))
        {
    		QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant 2. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    }
    if (!player3Name->text().isEmpty())
    {
        if (!addPlayer(player3Name->text(),player3Character->text(),player3Origin->text(),player3Description->text(),playerID3,errStr))
        {
    		QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant 3. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    }
    if (!player4Name->text().isEmpty())
    {
        if (!addPlayer(player4Name->text(),player4Character->text(),player4Origin->text(),player4Description->text(),playerID4,errStr))
        {
    		QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant 4. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    }
    if (!player5Name->text().isEmpty())
    {
        if (!addPlayer(player5Name->text(),player5Character->text(),player5Origin->text(),player5Description->text(),playerID5,errStr))
        {
    		QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant 5. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    }
    if (!player6Name->text().isEmpty())
    {
        if (!addPlayer(player6Name->text(),player6Character->text(),player6Origin->text(),player6Description->text(),playerID6,errStr))
        {
    		QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant 6. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    }
    // get next order number
    QSqlQuery orderQuery;
    int order=-1;
    if (orderQuery.exec("SELECT MAX(\"order\") AS max_order FROM entry"))
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
    sqlString = "INSERT INTO entry (\"order\", description, group_name, register_date, category_id, craft_judged, player_1_id";
    QString entryStr = entryComments->toPlainText();
    QString announcerStr = announcerNotes->toPlainText();
    QString soundStr = soundNotes->toPlainText();
    if (playerID2 != -1)
        sqlString.append(", player_2_id");
    if (playerID3 != -1)
        sqlString.append(", player_3_id");
    if (playerID4 != -1)
        sqlString.append(", player_4_id");
    if (playerID5 != -1)
        sqlString.append(", player_5_id");
    if (playerID6 != -1)
        sqlString.append(", player_6_id");
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
    sqlString.append(") VALUES (");
    int catID=getCategoryID();
    QString craftJudged = (craftmanship->isChecked() ? "true" : "false");
    sqlString.append(QString("%1, '%2', '%3', now(), %4, %5, %6")
                    .arg(order)
                    .arg(DBUtility::quote(entryDescription->text()))
                    .arg(DBUtility::quote(groupName->text()))
                    .arg(catID)
                    .arg(craftJudged)
                    .arg(playerID1));
    if (playerID2 != -1)
        sqlString.append(QString(", %1").arg(playerID2));
    if (playerID3 != -1)
        sqlString.append(QString(", %1").arg(playerID3));
    if (playerID4 != -1)
        sqlString.append(QString(", %1").arg(playerID4));
    if (playerID5 != -1)
        sqlString.append(QString(", %1").arg(playerID5));
    if (playerID6 != -1)
        sqlString.append(QString(", %1").arg(playerID6));
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
    sqlString.append(")");
    QSqlQuery addEntryQuery;
    if (!addEntryQuery.exec(sqlString))
    {
        QMessageBox::critical(this,"Unable to add entry",QString("Unable to add entry to database. Error: %1").arg(addEntryQuery.lastError().text()));
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

void
DialogNewEntry::updatePlayer1Desc()
{
    updatePlayerDescription(1);
}

void
DialogNewEntry::updatePlayer2Desc()
{
    updatePlayerDescription(2);
}

void
DialogNewEntry::updatePlayer3Desc()
{
    updatePlayerDescription(3);
}

void
DialogNewEntry::updatePlayer4Desc()
{
    updatePlayerDescription(4);
}

void
DialogNewEntry::updatePlayer5Desc()
{
    updatePlayerDescription(5);
}

void
DialogNewEntry::updatePlayer6Desc()
{
    updatePlayerDescription(6);
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
DialogNewEntry::addPlayer(QString name, QString character, QString origin, QString desc, int& playerID, QString& errStr)
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
    QRegExp rxContestant1("Contestant #1's Name: ([^\\n]+)");
    pos = rxContestant1.indexIn(formText);
    if (pos > -1)
    {
        player1Name->setText(rxContestant1.cap(1));
        somethingSet=true;
    }
    QRegExp rxContestant2("Contestant #2's Name: ([^\\n]+)");
    pos = rxContestant2.indexIn(formText);
    if (pos > -1)
    {
        player2Name->setText(rxContestant2.cap(1));
        somethingSet=true;
    }
    QRegExp rxContestant3("Contestant #3's Name: ([^\\n]+)");
    pos = rxContestant3.indexIn(formText);
    if (pos > -1)
    {
        player3Name->setText(rxContestant3.cap(1));
        somethingSet=true;
    }
    QRegExp rxContestant4("Contestant #4's Name: ([^\\n]+)");
    pos = rxContestant4.indexIn(formText);
    if (pos > -1)
    {
        player4Name->setText(rxContestant4.cap(1));
        somethingSet=true;
    }
    QRegExp rxContestant5("Contestant #5's Name: ([^\\n]+)");
    pos = rxContestant5.indexIn(formText);
    if (pos > -1)
    {
        player5Name->setText(rxContestant5.cap(1));
        somethingSet=true;
    }
    QRegExp rxContestant6("Contestant #6's Name: ([^\\n]+)");
    pos = rxContestant6.indexIn(formText);
    if (pos > -1)
    {
        player6Name->setText(rxContestant6.cap(1));
        somethingSet=true;
    }
    QRegExp rxScript("Script: ([^\\n]+)");
    pos = rxScript.indexIn(formText);
    if (pos > -1)
    {
        scriptUrl->setText(rxScript.cap(1));
        somethingSet=true;
    }
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
            entryDescription->setText(DescriptionUtil::getDescriptionSingle(player1Name->text(),player1Character->text(),player1Origin->text()));
    } else
    {
        entryDescription->setText(DescriptionUtil::getDescriptionSingle(player1Name->text(),player1Character->text(),player1Origin->text()));
    }
    for (int ii=1; ii <= 6; ++ii)
        updatePlayerDescription(ii);
}

void
DialogNewEntry::updatePlayerDescription(int playerIndex)
{
    QString playerName, playerChar, playerOrigin;
    QLineEdit* descText;
    switch (playerIndex)
    {
    case 1:
        playerName   = player1Name->text();
        playerChar   = player1Character->text();
        playerOrigin = player1Origin->text();
        descText = player1Description;
        break;
    case 2:
        playerName   = player2Name->text();
        playerChar   = player2Character->text();
        playerOrigin = player2Origin->text();
        descText = player2Description;
        break;
    case 3:
        playerName   = player3Name->text();
        playerChar   = player3Character->text();
        playerOrigin = player3Origin->text();
        descText = player3Description;
        break;
    case 4:
        playerName   = player4Name->text();
        playerChar   = player4Character->text();
        playerOrigin = player4Origin->text();
        descText = player4Description;
        break;
    case 5:
        playerName   = player5Name->text();
        playerChar   = player5Character->text();
        playerOrigin = player5Origin->text();
        descText = player5Description;
        break;
    case 6:
        playerName   = player6Name->text();
        playerChar   = player6Character->text();
        playerOrigin = player6Origin->text();
        descText = player6Description;
        break;
    }
    descText->setText(DescriptionUtil::getDescriptionSingle(playerName,playerChar,playerOrigin));
}

void
DialogNewEntry::clearDataFields()
{
}

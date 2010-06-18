#include <QtGui>
#include <QtSql>

#include "DialogNewEntry.h"
#include "DBUtility.h"

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
    categoryGroup->addButton(catNotSet);
    categoryGroup->addButton(catSkit);
    categoryGroup->addButton(catBeginner);
    categoryGroup->addButton(catIntermediate);
    categoryGroup->addButton(catMaster);
    catNotSet->setChecked(true);
    mainFormLayout->addRow("Category:",catLayout);
    craftmanship = new QCheckBox();
    mainFormLayout->addRow("Craftmanship?",craftmanship);
    QHBoxLayout* player1Layout = new QHBoxLayout();
    player1Layout->addWidget(new QLabel("Name:"));
    player1Name = new QLineEdit();
    player1Layout->addWidget(player1Name);
    player1Layout->addWidget(new QLabel("Character:"));
    player1Character = new QLineEdit();
    player1Layout->addWidget(player1Character);
    mainFormLayout->addRow("Contestant 1:",player1Layout);
    QHBoxLayout* player2Layout = new QHBoxLayout();
    player2Layout->addWidget(new QLabel("Name:"));
    player2Name = new QLineEdit();
    player2Layout->addWidget(player2Name);
    player2Layout->addWidget(new QLabel("Character:"));
    player2Character = new QLineEdit();
    player2Layout->addWidget(player2Character);
    mainFormLayout->addRow("Contestant 2:",player2Layout);
    QHBoxLayout* player3Layout = new QHBoxLayout();
    player3Layout->addWidget(new QLabel("Name:"));
    player3Name = new QLineEdit();
    player3Layout->addWidget(player3Name);
    player3Layout->addWidget(new QLabel("Character:"));
    player3Character = new QLineEdit();
    player3Layout->addWidget(player3Character);
    mainFormLayout->addRow("Contestant 3:",player3Layout);
    QHBoxLayout* player4Layout = new QHBoxLayout();
    player4Layout->addWidget(new QLabel("Name:"));
    player4Name = new QLineEdit();
    player4Layout->addWidget(player4Name);
    player4Layout->addWidget(new QLabel("Character:"));
    player4Character = new QLineEdit();
    player4Layout->addWidget(player4Character);
    mainFormLayout->addRow("Contestant 4:",player4Layout);
    QHBoxLayout* player5Layout = new QHBoxLayout();
    player5Layout->addWidget(new QLabel("Name:"));
    player5Name = new QLineEdit();
    player5Layout->addWidget(player5Name);
    player5Layout->addWidget(new QLabel("Character:"));
    player5Character = new QLineEdit();
    player5Layout->addWidget(player5Character);
    mainFormLayout->addRow("Contestant 5:",player5Layout);
    QHBoxLayout* player6Layout = new QHBoxLayout();
    player6Layout->addWidget(new QLabel("Name:"));
    player6Name = new QLineEdit();
    player6Layout->addWidget(player6Name);
    player6Layout->addWidget(new QLabel("Character:"));
    player6Character = new QLineEdit();
    player6Layout->addWidget(player6Character);
    mainFormLayout->addRow("Contestant 6:",player6Layout);
    scriptUrl = new QLineEdit();
    mainFormLayout->addRow("Script URL:",scriptUrl);
    mainLayout->addLayout(mainFormLayout);
    mainLayout->addWidget(new QLabel("Entry comments:"));
    entryComments = new QTextEdit();
    mainLayout->addWidget(entryComments);
    mainLayout->addWidget(new QLabel("Origin:"));
    originComments = new QTextEdit();
    originComments->setMaximumHeight(50);
    mainLayout->addWidget(originComments);
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
        if (!addPlayer(player1Name->text(),player1Character->text(),playerID1,errStr))
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
        if (!addPlayer(player2Name->text(),player2Character->text(),playerID2,errStr))
        {
    		QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant 2. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    }
    if (!player3Name->text().isEmpty())
    {
        if (!addPlayer(player3Name->text(),player3Character->text(),playerID3,errStr))
        {
    		QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant 3. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    }
    if (!player4Name->text().isEmpty())
    {
        if (!addPlayer(player4Name->text(),player4Character->text(),playerID4,errStr))
        {
    		QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant 4. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    }
    if (!player5Name->text().isEmpty())
    {
        if (!addPlayer(player5Name->text(),player5Character->text(),playerID5,errStr))
        {
    		QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant 5. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    }
    if (!player6Name->text().isEmpty())
    {
        if (!addPlayer(player6Name->text(),player6Character->text(),playerID6,errStr))
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
    QString originStr = originComments->toPlainText();
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
    if (!originStr.isEmpty())
        sqlString.append(", origin");
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
    if (!originStr.isEmpty())
        sqlString.append(QString(", '%1'").arg(DBUtility::quote(originStr)));
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
DialogNewEntry::addPlayer(QString name, QString character, int& playerID, QString& errStr)
{
    QString sqlString;
    sqlString = "INSERT INTO performer (real_name";
    if (!character.isEmpty())
    {
        sqlString.append(", character_name");
    }
    sqlString.append(") VALUES ('");
    sqlString.append(DBUtility::quote(name));
    sqlString.append("'");
    if (!character.isEmpty())
    {
        sqlString.append(", '");
        sqlString.append(DBUtility::quote(character));
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
    if (!player2Name->text().isEmpty())
    {
        // assume it's a skit ('group name' performing 'skit name')
    } else
    {
        // otherwise, assume one person:
        // 'real name' as 'character' from 'origin'
        QString description;
        QString realName=player1Name->text();
        QString charName=player1Character->text();
        QString origin=originComments->toPlainText();
        if (!realName.isEmpty())
        {
            description = realName;
            if (!charName.isEmpty())
                description.append(QString(" as %1").arg(charName));
            if (!origin.isEmpty())
                description.append(QString(" from %1").arg(origin));
        } else if (!charName.isEmpty())
        {
            description = charName;
            if (!origin.isEmpty())
                description.append(QString(" from %1").arg(origin));
        }
        entryDescription->setText(description);
    }
}

void
DialogNewEntry::clearDataFields()
{
}

#include <QtGui>
#include <QtSql>

#include "DialogModEntry.h"
#include "DBUtility.h"

DialogModEntry::DialogModEntry(QWidget* parent)
              : QDialog(parent),
                descriptionChanged(false),
                groupNameChanged(false),
                skitNameChanged(false),
                groupEMailChanged(false),
                scriptUrlChanged(false),
                confirmedChanged(false),
                formSentChanged(false),
                formReceivedChanged(false),
                craftmanshipChanged(false),
                categoryChanged(false),
                entryCommentsChanged(false),
                originCommentsChanged(false),
                announcerNotesChanged(false),
                soundNotesChanged(false),
                selected_(false),
                player1id(-1),
                player2id(-1),
                player3id(-1),
                player4id(-1),
                player5id(-1),
                player6id(-1),
                idEntry(-1),
                currentRow(-1),
                breakFast(false)
{
    setWindowIcon(QIcon(":/images/mod_entry.png"));
    setWindowTitle("Modify entry");

    summaryModel = new QSqlQueryModel();
    summaryModel->setQuery("SELECT * FROM mod_entry_summary");
    summaryModel->setHeaderData(0, Qt::Horizontal, tr("Order"));
    summaryModel->setHeaderData(1, Qt::Horizontal, tr("Group"));
    summaryModel->setHeaderData(2, Qt::Horizontal, tr("Real name 1"));

    summaryView = new QTableView();
    connect(summaryView,SIGNAL(clicked(const QModelIndex&)),this,SLOT(entrySelected(const QModelIndex&)));
    summaryView->setModel(summaryModel);
    summaryView->setColumnHidden(3,true);
    summaryView->show();
    QVBoxLayout* dialogLayout = new QVBoxLayout();
    QHBoxLayout* containerLayout = new QHBoxLayout();
    containerLayout->addWidget(summaryView);

    // add modification widgets
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QGroupBox* statusBox = new QGroupBox("Entry status");
    statusConfirmed = new QCheckBox("Confirmed?");
    craftFormSent = new QCheckBox("Craftmanship form sent?");
    craftFormReceived = new QCheckBox("Craftmanship form received?");
    QVBoxLayout* statusLayout = new QVBoxLayout();
    statusLayout->addWidget(statusConfirmed);
    statusLayout->addWidget(craftFormSent);
    statusLayout->addWidget(craftFormReceived);
    statusBox->setLayout(statusLayout);
    mainLayout->addWidget(statusBox);
    QFormLayout* mainFormLayout = new QFormLayout();
    entryDescription = new QLineEdit();
    mainFormLayout->addRow("Description:",entryDescription);
    skitName = new QLineEdit();
    mainFormLayout->addRow("Skit name:",skitName);
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
    player1Layout->addWidget(new QLabel("Prereg:"));
    player1Prereg = new QLineEdit();
    player1Layout->addWidget(player1Prereg);
    mainFormLayout->addRow("Contestant 1:",player1Layout);
    QHBoxLayout* player2Layout = new QHBoxLayout();
    player2Layout->addWidget(new QLabel("Name:"));
    player2Name = new QLineEdit();
    player2Layout->addWidget(player2Name);
    player2Layout->addWidget(new QLabel("Character:"));
    player2Character = new QLineEdit();
    player2Layout->addWidget(player2Character);
    player2Layout->addWidget(new QLabel("Prereg:"));
    player2Prereg = new QLineEdit();
    player2Layout->addWidget(player2Prereg);
    mainFormLayout->addRow("Contestant 2:",player2Layout);
    QHBoxLayout* player3Layout = new QHBoxLayout();
    player3Layout->addWidget(new QLabel("Name:"));
    player3Name = new QLineEdit();
    player3Layout->addWidget(player3Name);
    player3Layout->addWidget(new QLabel("Character:"));
    player3Character = new QLineEdit();
    player3Layout->addWidget(player3Character);
    player3Layout->addWidget(new QLabel("Prereg:"));
    player3Prereg = new QLineEdit();
    player3Layout->addWidget(player3Prereg);
    mainFormLayout->addRow("Contestant 3:",player3Layout);
    QHBoxLayout* player4Layout = new QHBoxLayout();
    player4Layout->addWidget(new QLabel("Name:"));
    player4Name = new QLineEdit();
    player4Layout->addWidget(player4Name);
    player4Layout->addWidget(new QLabel("Character:"));
    player4Character = new QLineEdit();
    player4Layout->addWidget(player4Character);
    player4Layout->addWidget(new QLabel("Prereg:"));
    player4Prereg = new QLineEdit();
    player4Layout->addWidget(player4Prereg);
    mainFormLayout->addRow("Contestant 4:",player4Layout);
    QHBoxLayout* player5Layout = new QHBoxLayout();
    player5Layout->addWidget(new QLabel("Name:"));
    player5Name = new QLineEdit();
    player5Layout->addWidget(player5Name);
    player5Layout->addWidget(new QLabel("Character:"));
    player5Character = new QLineEdit();
    player5Layout->addWidget(player5Character);
    player5Layout->addWidget(new QLabel("Prereg:"));
    player5Prereg = new QLineEdit();
    player5Layout->addWidget(player5Prereg);
    mainFormLayout->addRow("Contestant 5:",player5Layout);
    QHBoxLayout* player6Layout = new QHBoxLayout();
    player6Layout->addWidget(new QLabel("Name:"));
    player6Name = new QLineEdit();
    player6Layout->addWidget(player6Name);
    player6Layout->addWidget(new QLabel("Character:"));
    player6Character = new QLineEdit();
    player6Layout->addWidget(player6Character);
    player6Layout->addWidget(new QLabel("Prereg:"));
    player6Prereg = new QLineEdit();
    player6Layout->addWidget(player6Prereg);
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
    QWidget* containerWidget = new QWidget(this);
    //containerWidget->setMaximumWidth(600);
    containerWidget->setLayout(mainLayout);
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidget(containerWidget);
    containerLayout->addWidget(scrollArea);
    // end of modification widgets
    dialogLayout->addLayout(containerLayout);
    QDialogButtonBox* buttonBox = new QDialogButtonBox();
    buttonBox->addButton(QDialogButtonBox::Ok);
    buttonBox->addButton(QDialogButtonBox::Cancel);
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
    connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
    dialogLayout->addWidget(buttonBox);

    setLayout(dialogLayout);
    loadSettings();

    connect(entryDescription,SIGNAL(textEdited(const QString&)),this,SLOT(handleTextChanged(const QString&)));
    connect(groupName,SIGNAL(textEdited(const QString&)),this,SLOT(handleTextChanged(const QString&)));
    connect(skitName,SIGNAL(textEdited(const QString&)),this,SLOT(handleTextChanged(const QString&)));
    connect(groupEMail,SIGNAL(textEdited(const QString&)),this,SLOT(handleTextChanged(const QString&)));
    connect(scriptUrl,SIGNAL(textEdited(const QString&)),this,SLOT(handleTextChanged(const QString&)));

    connect(statusConfirmed,SIGNAL(toggled(bool)),this,SLOT(handleBtnToggle(bool)));
    connect(craftFormSent,SIGNAL(toggled(bool)),this,SLOT(handleBtnToggle(bool)));
    connect(craftFormReceived,SIGNAL(toggled(bool)),this,SLOT(handleBtnToggle(bool)));
    connect(craftmanship,SIGNAL(toggled(bool)),this,SLOT(handleBtnToggle(bool)));
    connect(catNotSet,SIGNAL(toggled(bool)),this,SLOT(handleBtnToggle(bool)));
    connect(catSkit,SIGNAL(toggled(bool)),this,SLOT(handleBtnToggle(bool)));
    connect(catBeginner,SIGNAL(toggled(bool)),this,SLOT(handleBtnToggle(bool)));
    connect(catIntermediate,SIGNAL(toggled(bool)),this,SLOT(handleBtnToggle(bool)));
    connect(catMaster,SIGNAL(toggled(bool)),this,SLOT(handleBtnToggle(bool)));

    connect(entryComments,SIGNAL(textChanged()),this,SLOT(handleTextEditChanged()));
    connect(originComments,SIGNAL(textChanged()),this,SLOT(handleTextEditChanged()));
    connect(announcerNotes,SIGNAL(textChanged()),this,SLOT(handleTextEditChanged()));
    connect(soundNotes,SIGNAL(textChanged()),this,SLOT(handleTextEditChanged()));
    //QTimer::singleShot(200,this,SLOT(showError()));
}

DialogModEntry::~DialogModEntry()
{
}

void
DialogModEntry::showError()
{
    //QMessageBox::information(this,"Error?",QString("Last DB error: %1").arg(summaryModel->lastError().text()));
}

void
DialogModEntry::accept()
{
    saveSettings();
    QDialog::accept();
}

void
DialogModEntry::reject()
{
    saveSettings();
    QDialog::reject();
}

void
DialogModEntry::loadSettings()
{
    QSettings settings;
    settings.beginGroup("ModEntryDialog");
    resize(settings.value("size",QSize(520,671)).toSize());
    move(settings.value("pos",QPoint(200,200)).toPoint());
    int sectSize = settings.value("w_0",-1).toInt();
    if (sectSize != -1)
        summaryView->horizontalHeader()->resizeSection(0,sectSize);
    sectSize = settings.value("w_1",-1).toInt();
    if (sectSize != -1)
        summaryView->horizontalHeader()->resizeSection(1,sectSize);
    sectSize = settings.value("w_2",-1).toInt();
    if (sectSize != -1)
        summaryView->horizontalHeader()->resizeSection(2,sectSize);
}

void
DialogModEntry::saveSettings()
{
    QSettings settings;
    settings.beginGroup("ModEntryDialog");
    settings.setValue("size",size());
    settings.setValue("pos",pos());
    settings.setValue("w_0",summaryView->horizontalHeader()->sectionSize(0));
    settings.setValue("w_1",summaryView->horizontalHeader()->sectionSize(1));
    settings.setValue("w_2",summaryView->horizontalHeader()->sectionSize(2));
    settings.endGroup();
}

void
DialogModEntry::refresh()
{
    summaryModel->setQuery("SELECT * FROM mod_entry_summary");
    if (currentRow != -1)
    {
        breakFast=true;
        summaryView->selectRow(currentRow);
    }
}

void
DialogModEntry::entrySelected(const QModelIndex & index)
{
    currentRow = index.row();
    qDebug("currentRow=%d",currentRow);
    // if current entry modified, save changes...
    if (selected_ && !breakFast)
    {
        updateEntry();
    } else
    {
        qDebug("Would have done infinite loop!");
    }
    breakFast=false;
    selected_ = true;

    descriptionChanged = false;
    groupNameChanged = false;
    skitNameChanged = false;
    groupEMailChanged = false;
    scriptUrlChanged = false;
    confirmedChanged = false;
    formSentChanged = false;
    formReceivedChanged = false;
    craftmanshipChanged = false;
    categoryChanged = false;
    entryCommentsChanged = false;
    originCommentsChanged = false;
    announcerNotesChanged = false;
    soundNotesChanged = false;

    // now load settings from selected entry
    QSqlRecord entry = summaryModel->record(currentRow);
    int order = entry.value("order").toInt();
    idEntry = entry.value("id_entry").toInt();
    QString gname = entry.value("group_name").toString();
    QString sqlString;
    sqlString.sprintf("SELECT * FROM entry where id_entry = %d",idEntry);
    QSqlQuery getEntryQuery;
    if (!getEntryQuery.exec(sqlString))
    {
        QMessageBox::critical(this,"Unable to get entry info",QString("Unable to get entry info from database. Error: %1").arg(getEntryQuery.lastError().text()));
        return;
    }
    if (getEntryQuery.next())
    {
        QString contactEmail = getEntryQuery.record().value("contact_email").toString();
        QString origin = getEntryQuery.record().value("origin").toString();
        QString entryCmt = getEntryQuery.record().value("notes_entry").toString();
        QString soundCmt = getEntryQuery.record().value("notes_sound").toString();
        QString announceCmt = getEntryQuery.record().value("notes_announcer").toString();
        QString desc = getEntryQuery.record().value("description").toString();
        QString grpName = getEntryQuery.record().value("group_name").toString();
        QString script = getEntryQuery.record().value("script_url").toString();
        QString sktName = getEntryQuery.record().value("skit_name").toString();
        bool craftJudged = getEntryQuery.record().value("craft_judged").toBool();
        bool isConfirmed = getEntryQuery.record().value("confirmed").toBool();
        bool formSent = getEntryQuery.record().value("craft_form_sent").toBool();
        bool formReceived = getEntryQuery.record().value("craft_form_received").toBool();
        int catID = getEntryQuery.record().value("category_id").toInt();

        statusConfirmed->setChecked(isConfirmed);
        craftFormSent->setChecked(formSent);
        craftFormReceived->setChecked(formReceived);
        groupEMail->setText(contactEmail);
        entryComments->setText(entryCmt);
        originComments->setText(origin);
        announcerNotes->setText(announceCmt);
        soundNotes->setText(soundCmt);
	    entryDescription->setText(desc);
        skitName->setText(sktName);
	    groupName->setText(grpName);
	    scriptUrl->setText(script);
	    craftmanship->setChecked(craftJudged);
        entryCommentsChanged = false;
        originCommentsChanged = false;
        announcerNotesChanged = false;
        soundNotesChanged = false;
        if (catID == 1)
            catSkit->setChecked(true);
        else if (catID == 2)
            catBeginner->setChecked(true);
        else if (catID == 3)
            catIntermediate->setChecked(true);
        else if (catID == 4)
            catMaster->setChecked(true);
        else
            catNotSet->setChecked(true);
        // set the contestant info
        int player_id = getEntryQuery.record().value("player_1_id").toInt();
        player1id = player_id;
        QString realName, charName;
        if (!getPlayerName(realName, charName, player_id))
            return;
        player1Name->setText(realName);
        player1Character->setText(charName);
        if (!getEntryQuery.record().isNull("player_2_id"))
        {
            player2id = player_id = getEntryQuery.record().value("player_2_id").toInt();
            if (!getPlayerName(realName, charName, player_id))
                return;
            player2Name->setText(realName);
            player2Character->setText(charName);
        } else
        {
            player2Name->setText("");
            player2Character->setText("");
            player2id = -1;
        }
        if (!getEntryQuery.record().isNull("player_3_id"))
        {
            player3id = player_id = getEntryQuery.record().value("player_3_id").toInt();
            if (!getPlayerName(realName, charName, player_id))
                return;
            player3Name->setText(realName);
            player3Character->setText(charName);
        } else
        {
            player3Name->setText("");
            player3Character->setText("");
            player3id = -1;
        }
        if (!getEntryQuery.record().isNull("player_4_id"))
        {
            player4id = player_id = getEntryQuery.record().value("player_4_id").toInt();
            if (!getPlayerName(realName, charName, player_id))
                return;
            player4Name->setText(realName);
            player4Character->setText(charName);
        } else
        {
            player4Name->setText("");
            player4Character->setText("");
            player4id = -1;
        }
        if (!getEntryQuery.record().isNull("player_5_id"))
        {
            player5id = player_id = getEntryQuery.record().value("player_5_id").toInt();
            if (!getPlayerName(realName, charName, player_id))
                return;
            player5Name->setText(realName);
            player5Character->setText(charName);
        } else
        {
            player5Name->setText("");
            player5Character->setText("");
            player5id = -1;
        }
        if (!getEntryQuery.record().isNull("player_6_id"))
        {
            player6id = player_id = getEntryQuery.record().value("player_6_id").toInt();
            if (!getPlayerName(realName, charName, player_id))
                return;
            player6Name->setText(realName);
            player6Character->setText(charName);
        } else
        {
            player6Name->setText("");
            player6Character->setText("");
            player6id = -1;
        }
    }
    //qDebug("Selected group '%s' at order %d, contact_email=%s",qPrintable(gname),order,qPrintable(contactEmail));
}

void
DialogModEntry::updateEntry()
{
    QSqlDatabase db(QSqlDatabase::database());
    if (!db.transaction())
    {
        QMessageBox::critical(this,"Unable to start transaction",QString("Unable to start database transaction. Error: %1").arg(db.lastError().text()));
        return;
    }
    QString errStr;
    // update player 1
    if (!updatePlayer(player1Name->text(),player1Character->text(),player1id,errStr))
    {
        QMessageBox::critical(this,"Unable to update contestant",QString("Unable to save contestant 1. Error: %1").arg(errStr));
        db.rollback();
        return;
    }
    // take care of adding/removing entries (can only be for entries 2-6)
    if (player2id != -1 && player2Name->text().isEmpty() && player2Character->text().isEmpty())
    {
        // delete player 2
        if (!deletePerformer(player2id,2))
        {
            db.rollback();
            return;
        }
    } else if (player2id == -1 && (!player2Name->text().isEmpty() || !player2Character->text().isEmpty()))
    {
        // add player 2
        if (!addPlayer(player2Name->text(),player2Character->text(),2,errStr))
        {
            QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant 2. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    } else if (player2id != -1)
    {
        // update player 2
        if (!updatePlayer(player2Name->text(),player2Character->text(),player2id,errStr))
        {
            QMessageBox::critical(this,"Unable to update contestant",QString("Unable to save contestant 2. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    }
    if (player3id != -1 && player3Name->text().isEmpty() && player3Character->text().isEmpty())
    {
        // delete player 3
        if (!deletePerformer(player3id,3))
        {
            db.rollback();
            return;
        }
    } else if (player3id == -1 && (!player3Name->text().isEmpty() || !player3Character->text().isEmpty()))
    {
        // add player 3
        if (!addPlayer(player3Name->text(),player3Character->text(),3,errStr))
        {
            QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant 3. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    } else if (player3id != -1)
    {
        // update player 3
        if (!updatePlayer(player3Name->text(),player3Character->text(),player3id,errStr))
        {
            QMessageBox::critical(this,"Unable to update contestant",QString("Unable to save contestant 3. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    }
    if (player4id != -1 && player4Name->text().isEmpty() && player4Character->text().isEmpty())
    {
        // delete player 4
        if (!deletePerformer(player4id,4))
        {
            db.rollback();
            return;
        }
    } else if (player4id == -1 && (!player4Name->text().isEmpty() || !player4Character->text().isEmpty()))
    {
        // add player 4
        if (!addPlayer(player4Name->text(),player4Character->text(),4,errStr))
        {
            QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant 4. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    } else if (player4id != -1)
    {
        // update player 4
        if (!updatePlayer(player4Name->text(),player4Character->text(),player4id,errStr))
        {
            QMessageBox::critical(this,"Unable to update contestant",QString("Unable to save contestant 4. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    }
    if (player5id != -1 && player5Name->text().isEmpty() && player5Character->text().isEmpty())
    {
        // delete player 5
        if (!deletePerformer(player5id,5))
        {
            db.rollback();
            return;
        }
    } else if (player5id == -1 && (!player5Name->text().isEmpty() || !player5Character->text().isEmpty()))
    {
        // add player 5
        if (!addPlayer(player5Name->text(),player5Character->text(),5,errStr))
        {
            QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant 5. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    } else if (player5id != -1)
    {
        // update player 5
        if (!updatePlayer(player5Name->text(),player5Character->text(),player5id,errStr))
        {
            QMessageBox::critical(this,"Unable to update contestant",QString("Unable to save contestant 5. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    }
    if (player6id != -1 && player6Name->text().isEmpty() && player6Character->text().isEmpty())
    {
        // delete player6
        if (!deletePerformer(player6id,6))
        {
            db.rollback();
            return;
        }
    } else if (player6id == -1 && (!player6Name->text().isEmpty() || !player6Character->text().isEmpty()))
    {
        // add player 6
        if (!addPlayer(player6Name->text(),player6Character->text(),6,errStr))
        {
            QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant 6. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    } else if (player6id != -1)
    {
        // update player 6
        if (!updatePlayer(player6Name->text(),player6Character->text(),player6id,errStr))
        {
            QMessageBox::critical(this,"Unable to update contestant",QString("Unable to save contestant 6. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    }
    // now update all other fields
    QString updateStringFields, updateStringValues;
    //updateStringFields = "group_name, confirmed, origin, category_id, contact_email, craft_judged, notes_entry, notes_announcer, notes_sound, description, skit_name";
    if (descriptionChanged)
        addUpdateField(updateStringFields, updateStringValues, "description", entryDescription->text());
    if (groupNameChanged)
        addUpdateField(updateStringFields, updateStringValues, "group_name", groupName->text());
    if (skitNameChanged)
        addUpdateField(updateStringFields, updateStringValues, "skit_name", skitName->text());
    if (groupEMailChanged)
        addUpdateField(updateStringFields, updateStringValues, "contact_email", groupEMail->text());
    if (scriptUrlChanged)
        addUpdateField(updateStringFields, updateStringValues, "script_url", scriptUrl->text());

    if (confirmedChanged)
    {
        QString value = (statusConfirmed->checkState() == Qt::Checked) ? "true" : "false";
        addUpdateField(updateStringFields, updateStringValues, "confirmed", value);
    }
    if (formSentChanged)
    {
        QString value = (craftFormSent->checkState() == Qt::Checked) ? "true" : "false";
        addUpdateField(updateStringFields, updateStringValues, "craft_form_sent", value);
    }
    if (formReceivedChanged)
    {
        QString value = (craftFormReceived->checkState() == Qt::Checked) ? "true" : "false";
        addUpdateField(updateStringFields, updateStringValues, "craft_form_received", value);
    }
    if (craftmanshipChanged)
    {
        QString value = (craftmanship->checkState() == Qt::Checked) ? "true" : "false";
        addUpdateField(updateStringFields, updateStringValues, "craft_judged", value);
    }
    if (categoryChanged)
    {
        int catID=5; // category not set ID
        if (catNotSet->isChecked())
            catID=5;
        else if (catSkit->isChecked())
            catID=1;
        else if (catBeginner->isChecked())
            catID=2;
        else if (catIntermediate->isChecked())
            catID=3;
        else if (catMaster->isChecked())
            catID=4;
        addUpdateField(updateStringFields, updateStringValues, "category_id", QString("%1").arg(catID));
    }
    if (entryCommentsChanged)
        addUpdateField(updateStringFields, updateStringValues, "notes_entry", entryComments->toPlainText());
    if (originCommentsChanged)
        addUpdateField(updateStringFields, updateStringValues, "origin", originComments->toPlainText());
    if (announcerNotesChanged)
        addUpdateField(updateStringFields, updateStringValues, "notes_announcer", announcerNotes->toPlainText());
    if (soundNotesChanged)
        addUpdateField(updateStringFields, updateStringValues, "notes_sound", soundNotes->toPlainText());
    qWarning("Update field=%s, value=%s",qPrintable(updateStringFields),qPrintable(updateStringValues));
    if (!updateStringFields.isEmpty())
    {
        QSqlQuery updateQuery;
        QString sqlString = QString("UPDATE entry SET (%1) = (%2) WHERE id_entry = %3").arg(updateStringFields).arg(updateStringValues).arg(idEntry);
        if (!updateQuery.exec(sqlString))
        {
            QMessageBox::critical(this,"Unable to update entry info",QString("Unable to update entry info to database. Error: %1").arg(updateQuery.lastError().text()));
            db.rollback();
            return;
        }
    }
    if (!db.commit())
    {
        QMessageBox::critical(this,"Unable to update",QString("Unable to coomit to NDK costume contest database. Error: %1").arg(db.lastError().text()));
        return;
    }
    refresh();
}

void
DialogModEntry::addUpdateField(QString& updateStringFields, QString& updateStringValues, const QString& fieldName, const QString& fieldValue)
{
    if (!updateStringFields.isEmpty())
    {
        updateStringFields.append(", ");
        updateStringValues.append(", ");
    }
    updateStringFields.append(fieldName);
    if (fieldValue.isEmpty())
        updateStringValues.append("null");
    else
        updateStringValues.append(QString("'%1'").arg(DBUtility::quote(fieldValue)));
}

bool
DialogModEntry::deletePerformer(int player_id, int playerIndex)
{
    QSqlQuery nullQuery, deleteQuery;
    if (!nullQuery.exec(QString("UPDATE entry SET player_%1_id = null where id_entry = %2").arg(playerIndex).arg(idEntry)))
    {
        QMessageBox::critical(this,"Unable to update entry info",QString("Unable to update entry info in database. Error: %1").arg(nullQuery.lastError().text()));
        return false;
    }
    if (!deleteQuery.exec(QString("DELETE FROM performer WHERE id_player = %1").arg(player_id)))
    {
        QMessageBox::critical(this,"Unable to update entry info",QString("Unable to delete performer from database. Error: %1").arg(deleteQuery.lastError().text()));
        return false;
    }
    return true;
}

bool
DialogModEntry::getPlayerName(QString& realName, QString& charName, int player_id)
{
    QSqlQuery entryQuery;
    if (!entryQuery.exec(QString("SELECT real_name, character_name from performer where id_player = %1").arg(player_id)))
    {
        QMessageBox::critical(this,"Unable to get entry's contestant info",QString("Unable to get entry's contestant info from database. Error: %1").arg(entryQuery.lastError().text()));
        return false;
    }
    if (entryQuery.next())
    {
        realName = entryQuery.record().value("real_name").toString();
        charName = entryQuery.record().value("character_name").toString();
    } else
        return false;
    return true;
}

bool
DialogModEntry::addPlayer(QString name, QString character, int playerIndex, QString& errStr)
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
    QSqlQuery query, updateQuery;
    if (query.exec(sqlString))
    {
        if (query.next())
        {
            int fieldNo = query.record().indexOf("id_player");
            int playerID = query.value(fieldNo).toInt();
            if (updateQuery.exec(QString("UPDATE entry SET player_%1_id = %2 WHERE id_entry = %3").arg(playerIndex).arg(playerID).arg(idEntry)))
            {
                return true;
            } else
            {
                errStr = updateQuery.lastError().text();
                return false;
            }
            //QMessageBox::information(this,"Added ID",QString("Added ID %1").arg(id_player));
        }
        return true;
    } else
    {
        errStr = query.lastError().text();
        return false;
    }
}

bool
DialogModEntry::updatePlayer(QString name, QString character, int playerID, QString& errStr)
{
    QString sqlString;
    sqlString = "UPDATE performer SET (real_name, character_name) = (";
    if (!name.isEmpty())
    {
        sqlString.append("'");
        sqlString.append(DBUtility::quote(name));
        sqlString.append("', ");
    } else
    {
        sqlString.append("null, ");
    }
    if (!character.isEmpty())
    {
        sqlString.append("'");
        sqlString.append(DBUtility::quote(character));
        sqlString.append("')");
    } else
    {
        sqlString.append("null)");
    }
    sqlString.append(QString(" WHERE id_player = %1").arg(playerID));
    qWarning("Update command: %s",qPrintable(sqlString));
    QSqlQuery query;
    if (query.exec(sqlString))
    {
        return true;
    } else
    {
        errStr = query.lastError().text();
        return false;
    }
}

void
DialogModEntry::handleTextChanged(const QString&)
{
    if (sender() == entryDescription)
        descriptionChanged = true;
    else if (sender() == groupName)
        groupNameChanged = true;
    else if (sender() == skitName)
        skitNameChanged = true;
    else if (sender() == groupEMail)
        groupEMailChanged = true;
    else if (sender() == scriptUrl)
        scriptUrlChanged = true;
}

void
DialogModEntry::handleBtnToggle(bool)
{
    if (sender() == craftmanship)
        craftmanshipChanged = true;
    else if (sender() == statusConfirmed)
        confirmedChanged = true;
    else if (sender() == craftFormSent)
        formSentChanged = true;
    else if (sender() == craftFormReceived)
        formReceivedChanged = true;
    else
        categoryChanged = true;
}

void
DialogModEntry::handleTextEditChanged()
{
    if (sender() == entryComments)
        entryCommentsChanged=true;
    else if (sender() == originComments)
        originCommentsChanged=true;
    else if (sender() == announcerNotes)
        announcerNotesChanged=true;
    else if (sender() == soundNotes)
        soundNotesChanged=true;
}

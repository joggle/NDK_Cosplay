#include <QtGui>
#include <QtSql>

#include "DialogModEntry.h"

DialogModEntry::DialogModEntry(QWidget* parent)
              : QDialog(parent)
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
}

void
DialogModEntry::entrySelected(const QModelIndex & index)
{
    int currentRow = index.row();
    qDebug("currentRow=%d",currentRow);
    // if current entry modified, save changes...

    // now load settings from selected entry
    QSqlRecord entry = summaryModel->record(currentRow);
    int order = entry.value("order").toInt();
    int id = entry.value("id_entry").toInt();
    QString gname = entry.value("group_name").toString();
    QString sqlString;
    sqlString.sprintf("SELECT * FROM entry where id_entry = %d",id);
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
	    bool craftJudged = getEntryQuery.record().value("craft_judged").toBool();
        int catID = getEntryQuery.record().value("category_id").toInt();

        groupEMail->setText(contactEmail);
        entryComments->setText(entryCmt);
        originComments->setText(origin);
        announcerNotes->setText(announceCmt);
        soundNotes->setText(soundCmt);
	    entryDescription->setText(desc);
	    groupName->setText(grpName);
	    scriptUrl->setText(script);
	    craftmanship->setChecked(craftJudged);
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
        QString realName, charName;
        if (!getPlayerName(realName, charName, player_id))
            return;
        player1Name->setText(realName);
        player1Character->setText(charName);
        if (!getEntryQuery.record().isNull("player_2_id"))
        {
            player_id = getEntryQuery.record().value("player_2_id").toInt();
            if (!getPlayerName(realName, charName, player_id))
                return;
            player2Name->setText(realName);
            player2Character->setText(charName);
        }
        if (!getEntryQuery.record().isNull("player_3_id"))
        {
            player_id = getEntryQuery.record().value("player_3_id").toInt();
            if (!getPlayerName(realName, charName, player_id))
                return;
            player3Name->setText(realName);
            player3Character->setText(charName);
        }
        if (!getEntryQuery.record().isNull("player_4_id"))
        {
            player_id = getEntryQuery.record().value("player_4_id").toInt();
            if (!getPlayerName(realName, charName, player_id))
                return;
            player4Name->setText(realName);
            player4Character->setText(charName);
        }
        if (!getEntryQuery.record().isNull("player_5_id"))
        {
            player_id = getEntryQuery.record().value("player_5_id").toInt();
            if (!getPlayerName(realName, charName, player_id))
                return;
            player5Name->setText(realName);
            player5Character->setText(charName);
        }
        if (!getEntryQuery.record().isNull("player_6_id"))
        {
            player_id = getEntryQuery.record().value("player_6_id").toInt();
            if (!getPlayerName(realName, charName, player_id))
                return;
            player6Name->setText(realName);
            player6Character->setText(charName);
        }
    }
    //qDebug("Selected group '%s' at order %d, contact_email=%s",qPrintable(gname),order,qPrintable(contactEmail));
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

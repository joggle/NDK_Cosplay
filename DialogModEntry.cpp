#include <QtGui>
#include <QtSql>

#include "DialogModEntry.h"
#include "DBUtility.h"
#include "DescriptionUtil.h"

DialogModEntry::DialogModEntry(QWidget* parent)
              : QDialog(parent),
                descriptionChanged(false),
                groupNameChanged(false),
                skitNameChanged(false),
                groupEMailChanged(false),
                scriptUrlChanged(false),
                musicUrlChanged(false),
                confirmedChanged(false),
                formSentChanged(false),
                formReceivedChanged(false),
                craftmanshipChanged(false),
                categoryChanged(false),
                entryCommentsChanged(false),
                announcerNotesChanged(false),
                soundNotesChanged(false),
                selected_(false),
                /*player1id(-1),
                player2id(-1),
                player3id(-1),
                player4id(-1),
                player5id(-1),
                player6id(-1),*/
                idEntry(-1),
                currentRow(-1),
                breakFast(false),
                selectedCategory(Unassigned)
{
    int ii;
    for (ii=0; ii < 6; ++ii)
        playerId[ii] = -1;
    setWindowIcon(QIcon(":/images/mod_entry.png"));
    setWindowTitle("Modify entry");

    QVBoxLayout* summaryLayout = new QVBoxLayout();

    // Unassigned entries (no category set yet)
    summaryModelUnassigned = new QSqlQueryModel();
    summaryModelUnassigned->setQuery("SELECT * FROM mod_entry_summary WHERE category_id = 5");
    //summaryModelUnassigned->setHeaderData(0, Qt::Horizontal, tr("Order"));
    summaryModelUnassigned->setHeaderData(1, Qt::Horizontal, tr("Group"));
    summaryModelUnassigned->setHeaderData(2, Qt::Horizontal, tr("Real name 1"));

    summaryViewUnassigned = new QTableView();
    connect(summaryViewUnassigned,SIGNAL(clicked(const QModelIndex&)),this,SLOT(entrySelected(const QModelIndex&)));
    summaryViewUnassigned->setModel(summaryModelUnassigned);
    summaryViewUnassigned->setColumnHidden(0,true);
    summaryViewUnassigned->setColumnHidden(3,true);
    summaryViewUnassigned->setColumnHidden(4,true);
    summaryViewUnassigned->show();
    summaryViewUnassigned->setMaximumWidth(400);
    summaryLayout->addWidget(new QLabel("Unassigned"));
    summaryLayout->addWidget(summaryViewUnassigned);

    // Children entries
    summaryModelChildren = new QSqlQueryModel();
    summaryModelChildren->setQuery("SELECT * FROM mod_entry_summary WHERE category_id = 6");
    //summaryModelBeginner->setHeaderData(0, Qt::Horizontal, tr("Order"));
    summaryModelChildren->setHeaderData(1, Qt::Horizontal, tr("Group"));
    summaryModelChildren->setHeaderData(2, Qt::Horizontal, tr("Real name 1"));

    summaryViewChildren = new QTableView();
    connect(summaryViewChildren,SIGNAL(clicked(const QModelIndex&)),this,SLOT(entrySelected(const QModelIndex&)));
    summaryViewChildren->setModel(summaryModelChildren);
    summaryViewChildren->setColumnHidden(0,true);
    summaryViewChildren->setColumnHidden(3,true);
    summaryViewChildren->setColumnHidden(4,true);
    summaryViewChildren->show();
    summaryViewChildren->setMaximumWidth(400);
    summaryLayout->addWidget(new QLabel("Children"));
    summaryLayout->addWidget(summaryViewChildren);

    // Beginner entries
    summaryModelBeginner = new QSqlQueryModel();
    summaryModelBeginner->setQuery("SELECT * FROM mod_entry_summary WHERE category_id = 2");
    //summaryModelBeginner->setHeaderData(0, Qt::Horizontal, tr("Order"));
    summaryModelBeginner->setHeaderData(1, Qt::Horizontal, tr("Group"));
    summaryModelBeginner->setHeaderData(2, Qt::Horizontal, tr("Real name 1"));

    summaryViewBeginner = new QTableView();
    connect(summaryViewBeginner,SIGNAL(clicked(const QModelIndex&)),this,SLOT(entrySelected(const QModelIndex&)));
    summaryViewBeginner->setModel(summaryModelBeginner);
    summaryViewBeginner->setColumnHidden(0,true);
    summaryViewBeginner->setColumnHidden(3,true);
    summaryViewBeginner->setColumnHidden(4,true);
    summaryViewBeginner->show();
    summaryViewBeginner->setMaximumWidth(400);
    summaryLayout->addWidget(new QLabel("Beginner"));
    summaryLayout->addWidget(summaryViewBeginner);

    // Intermediate entries
    summaryModelIntermediate = new QSqlQueryModel();
    summaryModelIntermediate->setQuery("SELECT * FROM mod_entry_summary WHERE category_id = 3");
    //summaryModelIntermediate->setHeaderData(0, Qt::Horizontal, tr("Order"));
    summaryModelIntermediate->setHeaderData(1, Qt::Horizontal, tr("Group"));
    summaryModelIntermediate->setHeaderData(2, Qt::Horizontal, tr("Real name 1"));

    summaryViewIntermediate = new QTableView();
    connect(summaryViewIntermediate,SIGNAL(clicked(const QModelIndex&)),this,SLOT(entrySelected(const QModelIndex&)));
    summaryViewIntermediate->setModel(summaryModelIntermediate);
    summaryViewIntermediate->setColumnHidden(0,true);
    summaryViewIntermediate->setColumnHidden(3,true);
    summaryViewIntermediate->setColumnHidden(4,true);
    summaryViewIntermediate->show();
    summaryViewIntermediate->setMaximumWidth(400);
    summaryLayout->addWidget(new QLabel("Intermediate"));
    summaryLayout->addWidget(summaryViewIntermediate);

    // Master entries
    summaryModelMaster = new QSqlQueryModel();
    summaryModelMaster->setQuery("SELECT * FROM mod_entry_summary WHERE category_id = 4");
    //summaryModelMaster->setHeaderData(0, Qt::Horizontal, tr("Order"));
    summaryModelMaster->setHeaderData(1, Qt::Horizontal, tr("Group"));
    summaryModelMaster->setHeaderData(2, Qt::Horizontal, tr("Real name 1"));

    summaryViewMaster = new QTableView();
    connect(summaryViewMaster,SIGNAL(clicked(const QModelIndex&)),this,SLOT(entrySelected(const QModelIndex&)));
    summaryViewMaster->setModel(summaryModelMaster);
    summaryViewMaster->setColumnHidden(0,true);
    summaryViewMaster->setColumnHidden(3,true);
    summaryViewMaster->setColumnHidden(4,true);
    summaryViewMaster->show();
    summaryViewMaster->setMaximumWidth(400);
    summaryLayout->addWidget(new QLabel("Master"));
    summaryLayout->addWidget(summaryViewMaster);

    // Skit entries
    summaryModelSkit = new QSqlQueryModel();
    summaryModelSkit->setQuery("SELECT * FROM mod_entry_summary WHERE category_id = 1");
    //summaryModelSkit->setHeaderData(0, Qt::Horizontal, tr("Order"));
    summaryModelSkit->setHeaderData(1, Qt::Horizontal, tr("Group"));
    summaryModelSkit->setHeaderData(2, Qt::Horizontal, tr("Real name 1"));

    summaryViewSkit = new QTableView();
    connect(summaryViewSkit,SIGNAL(clicked(const QModelIndex&)),this,SLOT(entrySelected(const QModelIndex&)));
    summaryViewSkit->setModel(summaryModelSkit);
    summaryViewSkit->setColumnHidden(0,true);
    summaryViewSkit->setColumnHidden(3,true);
    summaryViewSkit->setColumnHidden(4,true);
    summaryViewSkit->show();
    summaryViewSkit->setMaximumWidth(400);
    summaryLayout->addWidget(new QLabel("Skit"));
    summaryLayout->addWidget(summaryViewSkit);

    QVBoxLayout* dialogLayout = new QVBoxLayout();
    QHBoxLayout* containerLayout = new QHBoxLayout();
    containerLayout->addLayout(summaryLayout);

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
    QPushButton* updateDescBtn = new QPushButton("Update description");
    connect(updateDescBtn,SIGNAL(clicked()),this,SLOT(updateDescription()));
    QHBoxLayout* descLayout = new QHBoxLayout();
    descLayout->addWidget(entryDescription);
    descLayout->addWidget(updateDescBtn);
    mainFormLayout->addRow("Description:",descLayout);
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

    playerName = new QLineEdit*[6];
    playerCharacter = new QLineEdit*[6];
    playerOrigin = new QLineEdit*[6];
    playerDescription = new QLineEdit*[6];
    playerPrereg = new QLineEdit*[6];
    playerDescBtn = new QPushButton*[6];
    for (ii=0; ii < 6; ++ii)
    {
        playerName[ii] = new QLineEdit();
        playerCharacter[ii] = new QLineEdit();
        playerOrigin[ii] = new QLineEdit();
        playerDescription[ii] = new QLineEdit();
        playerPrereg[ii] = new QLineEdit();
        playerPrereg[ii]->setMaximumWidth(75);
        playerDescBtn[ii] = new QPushButton("Update description");
        playerDescBtn[ii]->setProperty("player_index",ii+1);
        connect(playerDescBtn[ii],SIGNAL(clicked()),this,SLOT(handlePlayerDescBtn()));
    }

    for (ii=1; ii <= 6; ++ii)
        addPlayerLayout(ii,mainFormLayout);

    /*QVBoxLayout* player1Layout = new QVBoxLayout();
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
    player1TopLayout->addWidget(new QLabel("Prereg:"));
    player1Prereg = new QLineEdit();
    player1Prereg->setMaximumWidth(75);
    player1TopLayout->addWidget(player1Prereg);
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
    player2TopLayout->addWidget(new QLabel("Prereg:"));
    player2Prereg = new QLineEdit();
    player2Prereg->setMaximumWidth(75);
    player2TopLayout->addWidget(player2Prereg);
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
    player3TopLayout->addWidget(new QLabel("Prereg:"));
    player3Prereg = new QLineEdit();
    player3Prereg->setMaximumWidth(75);
    player3TopLayout->addWidget(player3Prereg);
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
    player4TopLayout->addWidget(new QLabel("Prereg:"));
    player4Prereg = new QLineEdit();
    player4Prereg->setMaximumWidth(75);
    player4TopLayout->addWidget(player4Prereg);
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
    player5TopLayout->addWidget(new QLabel("Prereg:"));
    player5Prereg = new QLineEdit();
    player5Prereg->setMaximumWidth(75);
    player5TopLayout->addWidget(player5Prereg);
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
    player6TopLayout->addWidget(new QLabel("Prereg:"));
    player6Prereg = new QLineEdit();
    player6Prereg->setMaximumWidth(75);
    player6TopLayout->addWidget(player6Prereg);
    player6Layout->addLayout(player6TopLayout);
    player6BottomLayout->addWidget(new QLabel("Description:"));
    player6Description = new QLineEdit();
    player6BottomLayout->addWidget(player6Description);
    player6DescBtn = new QPushButton("Update description");
    player6BottomLayout->addWidget(player6DescBtn);
    connect(player6DescBtn,SIGNAL(clicked()),this,SLOT(updatePlayer6Desc()));
    player6Layout->addLayout(player6BottomLayout);
    mainFormLayout->addRow("Contestant 6:",player6Layout);*/

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
    QWidget* containerWidget = new QWidget(this);
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
    connect(musicUrl,SIGNAL(textEdited(const QString&)),this,SLOT(handleTextChanged(const QString&)));

    connect(statusConfirmed,SIGNAL(toggled(bool)),this,SLOT(handleBtnToggle(bool)));
    connect(craftFormSent,SIGNAL(toggled(bool)),this,SLOT(handleBtnToggle(bool)));
    connect(craftFormReceived,SIGNAL(toggled(bool)),this,SLOT(handleBtnToggle(bool)));
    connect(craftmanship,SIGNAL(toggled(bool)),this,SLOT(handleBtnToggle(bool)));
    connect(catNotSet,SIGNAL(toggled(bool)),this,SLOT(handleBtnToggle(bool)));
    connect(catSkit,SIGNAL(toggled(bool)),this,SLOT(handleBtnToggle(bool)));
    connect(catBeginner,SIGNAL(toggled(bool)),this,SLOT(handleBtnToggle(bool)));
    connect(catIntermediate,SIGNAL(toggled(bool)),this,SLOT(handleBtnToggle(bool)));
    connect(catMaster,SIGNAL(toggled(bool)),this,SLOT(handleBtnToggle(bool)));
    connect(catChildren,SIGNAL(toggled(bool)),this,SLOT(handleBtnToggle(bool)));

    connect(entryComments,SIGNAL(textChanged()),this,SLOT(handleTextEditChanged()));
    connect(announcerNotes,SIGNAL(textChanged()),this,SLOT(handleTextEditChanged()));
    connect(soundNotes,SIGNAL(textChanged()),this,SLOT(handleTextEditChanged()));
    //QTimer::singleShot(200,this,SLOT(showError()));
}

DialogModEntry::~DialogModEntry()
{
}

void
DialogModEntry::handlePlayerDescBtn()
{
    updatePlayerDescription(sender()->property("player_index").toInt());
}

void
DialogModEntry::addPlayerLayout(int playerID, QFormLayout* mainLayout)
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
    playerTopLayout->addWidget(new QLabel("Prereg:"));
    playerTopLayout->addWidget(playerPrereg[playerID-1]);
    playerLayout->addLayout(playerTopLayout);
    playerBottomLayout->addWidget(new QLabel("Description:"));
    playerBottomLayout->addWidget(playerDescription[playerID-1]);
    playerBottomLayout->addWidget(playerDescBtn[playerID-1]);
    playerLayout->addLayout(playerBottomLayout);
    mainLayout->addRow(QString("Contestant %1:").arg(playerID),playerLayout);
}

/*void
DialogModEntry::updatePlayer1Desc()
{
    updatePlayerDescription(1);
}

void
DialogModEntry::updatePlayer2Desc()
{
    updatePlayerDescription(2);
}

void
DialogModEntry::updatePlayer3Desc()
{
    updatePlayerDescription(3);
}

void
DialogModEntry::updatePlayer4Desc()
{
    updatePlayerDescription(4);
}

void
DialogModEntry::updatePlayer5Desc()
{
    updatePlayerDescription(5);
}

void
DialogModEntry::updatePlayer6Desc()
{
    updatePlayerDescription(6);
}*/

void
DialogModEntry::updatePlayerDescription(int playerIndex)
{
    playerDescription[playerIndex-1]->setText(DescriptionUtil::getDescriptionSingle(playerName[playerIndex-1]->text(),playerCharacter[playerIndex-1]->text(),playerOrigin[playerIndex-1]->text()));
    /*QString playerName, playerChar, playerOrigin;
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
    descText->setText(DescriptionUtil::getDescriptionSingle(playerName,playerChar,playerOrigin));*/
}

void
DialogModEntry::showError()
{
    //QMessageBox::information(this,"Error?",QString("Last DB error: %1").arg(summaryModel->lastError().text()));
}

void
DialogModEntry::updateDescription()
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
            //entryDescription->setText(DescriptionUtil::getDescriptionSingle(player1Name->text(),player1Character->text(),player1Origin->text()));
    } else
    {
        entryDescription->setText(DescriptionUtil::getDescriptionSingle(playerName[0]->text(),playerCharacter[0]->text(),playerOrigin[0]->text()));
        //entryDescription->setText(DescriptionUtil::getDescriptionSingle(player1Name->text(),player1Character->text(),player1Origin->text()));
    }
    descriptionChanged=true;
    for (int ii=1; ii <= 6; ++ii)
        updatePlayerDescription(ii);
}

void
DialogModEntry::accept()
{
    saveSettings();
    if (selected_)
        updateEntry();
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
    {
        summaryViewUnassigned->horizontalHeader()->resizeSection(0,sectSize);
        summaryViewBeginner->horizontalHeader()->resizeSection(0,sectSize);
        summaryViewIntermediate->horizontalHeader()->resizeSection(0,sectSize);
        summaryViewMaster->horizontalHeader()->resizeSection(0,sectSize);
        summaryViewSkit->horizontalHeader()->resizeSection(0,sectSize);
        summaryViewChildren->horizontalHeader()->resizeSection(0,sectSize);
    }
    sectSize = settings.value("w_1",-1).toInt();
    if (sectSize != -1)
    {
        summaryViewUnassigned->horizontalHeader()->resizeSection(1,sectSize);
        summaryViewBeginner->horizontalHeader()->resizeSection(1,sectSize);
        summaryViewIntermediate->horizontalHeader()->resizeSection(1,sectSize);
        summaryViewMaster->horizontalHeader()->resizeSection(1,sectSize);
        summaryViewSkit->horizontalHeader()->resizeSection(1,sectSize);
        summaryViewChildren->horizontalHeader()->resizeSection(1,sectSize);
    }
    sectSize = settings.value("w_2",-1).toInt();
    if (sectSize != -1)
    {
        summaryViewUnassigned->horizontalHeader()->resizeSection(2,sectSize);
        summaryViewBeginner->horizontalHeader()->resizeSection(2,sectSize);
        summaryViewIntermediate->horizontalHeader()->resizeSection(2,sectSize);
        summaryViewMaster->horizontalHeader()->resizeSection(2,sectSize);
        summaryViewSkit->horizontalHeader()->resizeSection(2,sectSize);
        summaryViewChildren->horizontalHeader()->resizeSection(2,sectSize);
    }
}

void
DialogModEntry::saveSettings()
{
    QSettings settings;
    settings.beginGroup("ModEntryDialog");
    settings.setValue("size",size());
    settings.setValue("pos",pos());
    settings.setValue("w_0",summaryViewUnassigned->horizontalHeader()->sectionSize(0));
    settings.setValue("w_1",summaryViewUnassigned->horizontalHeader()->sectionSize(1));
    settings.setValue("w_2",summaryViewUnassigned->horizontalHeader()->sectionSize(2));
    settings.endGroup();
}

void
DialogModEntry::refresh()
{
    summaryModelUnassigned->setQuery("SELECT * FROM mod_entry_summary WHERE category_id = 5");
    summaryModelBeginner->setQuery("SELECT * FROM mod_entry_summary WHERE category_id = 2");
    summaryModelIntermediate->setQuery("SELECT * FROM mod_entry_summary WHERE category_id = 3");
    summaryModelMaster->setQuery("SELECT * FROM mod_entry_summary WHERE category_id = 4");
    summaryModelSkit->setQuery("SELECT * FROM mod_entry_summary WHERE category_id = 1");
    summaryModelChildren->setQuery("SELECT * FROM mod_entry_summary WHERE category_id = 6");
    if (currentRow != -1)
    {
        breakFast=true;
        switch (selectedCategory)
        {
        case Unassigned:
            summaryViewUnassigned->selectRow(currentRow);
            break;
        case Beginner:
            summaryViewBeginner->selectRow(currentRow);
            break;
        case Intermediate:
            summaryViewIntermediate->selectRow(currentRow);
            break;
        case Master:
            summaryViewMaster->selectRow(currentRow);
            break;
        case Skit:
            summaryViewSkit->selectRow(currentRow);
            break;
        case Children:
            summaryViewChildren->selectRow(currentRow);
            break;
        }
    }
}

void
DialogModEntry::entrySelected(const QModelIndex & index)
{
    QSqlQueryModel* summaryModel=0;
    if (sender() == summaryViewUnassigned)
    {
        summaryModel = summaryModelUnassigned;
        selectedCategory = Unassigned;
    } else if (sender() == summaryViewBeginner)
    {
        summaryModel = summaryModelBeginner;
        selectedCategory = Beginner;
    } else if (sender() == summaryViewIntermediate)
    {
        summaryModel = summaryModelIntermediate;
        selectedCategory = Intermediate;
    } else if (sender() == summaryViewMaster)
    {
        summaryModel = summaryModelMaster;
        selectedCategory = Master;
    } else if (sender() == summaryViewSkit)
    {
        summaryModel = summaryModelSkit;
        selectedCategory = Skit;
    } else if (sender() == summaryViewChildren)
    {
        summaryModel = summaryModelChildren;
        selectedCategory = Children;
    }
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
    musicUrlChanged = false;
    confirmedChanged = false;
    formSentChanged = false;
    formReceivedChanged = false;
    craftmanshipChanged = false;
    categoryChanged = false;
    entryCommentsChanged = false;
    announcerNotesChanged = false;
    soundNotesChanged = false;

    // now load settings from selected entry
    QSqlRecord entry = summaryModel->record(currentRow);
    //--int order = entry.value("order").toInt();
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
        QString entryCmt = getEntryQuery.record().value("notes_entry").toString();
        QString soundCmt = getEntryQuery.record().value("notes_sound").toString();
        QString announceCmt = getEntryQuery.record().value("notes_announcer").toString();
        QString desc = getEntryQuery.record().value("description").toString();
        QString grpName = getEntryQuery.record().value("group_name").toString();
        QString script = getEntryQuery.record().value("script_url").toString();
        QString music = getEntryQuery.record().value("music_url").toString();
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
        announcerNotes->setText(announceCmt);
        soundNotes->setText(soundCmt);
	    entryDescription->setText(desc);
        skitName->setText(sktName);
	    groupName->setText(grpName);
	    scriptUrl->setText(script);
	    musicUrl->setText(music);
	    craftmanship->setChecked(craftJudged);
        entryCommentsChanged = false;
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
        else if (catID == 6)
            catChildren->setChecked(true);
        else
            catNotSet->setChecked(true);
        // set the contestant info
        int ii;
        for (ii=0; ii < 6; ++ii)
        {
            QString fieldName(QString("player_%1_id").arg(ii+1));
            if (!getEntryQuery.record().isNull(fieldName))
            {
                int player_id = getEntryQuery.record().value(fieldName).toInt();
                playerId[ii] = player_id;
                QString realName, charName, origin, playerDesc, prereg;
                if (!getPlayerName(realName, charName, origin, playerDesc, prereg, player_id))
                    return;
                playerName[ii]->setText(realName);
                playerCharacter[ii]->setText(charName);
                playerOrigin[ii]->setText(origin);
                playerDescription[ii]->setText(playerDesc);
                playerPrereg[ii]->setText(prereg);
            } else
            {
                playerName[ii]->setText("");
                playerCharacter[ii]->setText("");
                playerOrigin[ii]->setText("");
                playerDescription[ii]->setText("");
                playerPrereg[ii]->setText("");
                playerId[ii] = -1;
            }
        }
        /*if (!getEntryQuery.record().isNull("player_2_id"))
        {
            player2id = player_id = getEntryQuery.record().value("player_2_id").toInt();
            if (!getPlayerName(realName, charName, origin, playerDesc, prereg, player_id))
                return;
            player2Name->setText(realName);
            player2Character->setText(charName);
            player2Origin->setText(origin);
            player2Description->setText(playerDesc);
            player2Prereg->setText(prereg);
        } else
        {
            player2Name->setText("");
            player2Character->setText("");
            player2Origin->setText("");
            player2Description->setText("");
            player2Prereg->setText("");
            player2id = -1;
        }
        if (!getEntryQuery.record().isNull("player_3_id"))
        {
            player3id = player_id = getEntryQuery.record().value("player_3_id").toInt();
            if (!getPlayerName(realName, charName, origin, playerDesc, prereg, player_id))
                return;
            player3Name->setText(realName);
            player3Character->setText(charName);
            player3Origin->setText(origin);
            player3Description->setText(playerDesc);
            player3Prereg->setText(prereg);
        } else
        {
            player3Name->setText("");
            player3Character->setText("");
            player3Origin->setText("");
            player3Description->setText("");
            player3Prereg->setText("");
            player3id = -1;
        }
        if (!getEntryQuery.record().isNull("player_4_id"))
        {
            player4id = player_id = getEntryQuery.record().value("player_4_id").toInt();
            if (!getPlayerName(realName, charName, origin, playerDesc, prereg, player_id))
                return;
            player4Name->setText(realName);
            player4Character->setText(charName);
            player4Origin->setText(origin);
            player4Description->setText(playerDesc);
            player4Prereg->setText(prereg);
        } else
        {
            player4Name->setText("");
            player4Character->setText("");
            player4Origin->setText("");
            player4Description->setText("");
            player4Prereg->setText("");
            player4id = -1;
        }
        if (!getEntryQuery.record().isNull("player_5_id"))
        {
            player5id = player_id = getEntryQuery.record().value("player_5_id").toInt();
            if (!getPlayerName(realName, charName, origin, playerDesc, prereg, player_id))
                return;
            player5Name->setText(realName);
            player5Character->setText(charName);
            player5Origin->setText(origin);
            player5Description->setText(playerDesc);
            player5Prereg->setText(prereg);
        } else
        {
            player5Name->setText("");
            player5Character->setText("");
            player5Origin->setText("");
            player5Description->setText("");
            player5Prereg->setText("");
            player5id = -1;
        }
        if (!getEntryQuery.record().isNull("player_6_id"))
        {
            player6id = player_id = getEntryQuery.record().value("player_6_id").toInt();
            if (!getPlayerName(realName, charName, origin, playerDesc, prereg, player_id))
                return;
            player6Name->setText(realName);
            player6Character->setText(charName);
            player6Origin->setText(origin);
            player6Description->setText(playerDesc);
            player6Prereg->setText(prereg);
        } else
        {
            player6Name->setText("");
            player6Character->setText("");
            player6Origin->setText("");
            player6Description->setText("");
            player6Prereg->setText("");
            player6id = -1;
        }*/
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
    if (!updatePlayer(playerName[0]->text(),playerCharacter[0]->text(),playerOrigin[0]->text(),playerDescription[0]->text(),playerPrereg[0]->text(),playerId[0],errStr))
    {
        QMessageBox::critical(this,"Unable to update contestant",QString("Unable to save contestant 1. Error: %1").arg(errStr));
        db.rollback();
        return;
    }
    int ii;
    for (ii=1; ii < 6; ++ii)
    {
        if (playerId[ii] != -1 && playerName[ii]->text().isEmpty() && playerCharacter[ii]->text().isEmpty())
        {
            // delete player ii+1
            if (!deletePerformer(playerId[ii],2))
            {
                db.rollback();
                return;
            }
        } else if (playerId[ii] == -1 && (!playerName[ii]->text().isEmpty() || !playerCharacter[ii]->text().isEmpty()))
        {
            // add player ii+1
            if (!addPlayer(playerName[ii]->text(),playerCharacter[ii]->text(),playerOrigin[ii]->text(),playerDescription[ii]->text(),playerPrereg[ii]->text(),2,errStr))
            {
                QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant %1. Error: %2").arg(ii+1).arg(errStr));
                db.rollback();
                return;
            }
        } else if (playerId[ii] != -1)
        {
            // update player ii+1
            if (!updatePlayer(playerName[ii]->text(),playerCharacter[ii]->text(),playerOrigin[ii]->text(),playerDescription[ii]->text(),playerPrereg[ii]->text(),playerId[ii],errStr))
            {
                QMessageBox::critical(this,"Unable to update contestant",QString("Unable to save contestant %1. Error: %2").arg(ii+1).arg(errStr));
                db.rollback();
                return;
            }
        }
    }
    /*--if (!updatePlayer(player1Name->text(),player1Character->text(),player1Origin->text(),player1Description->text(),player1Prereg->text(),player1id,errStr))
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
        if (!addPlayer(player2Name->text(),player2Character->text(),player2Origin->text(),player2Description->text(),player2Prereg->text(),2,errStr))
        {
            QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant 2. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    } else if (player2id != -1)
    {
        // update player 2
        if (!updatePlayer(player2Name->text(),player2Character->text(),player2Origin->text(),player2Description->text(),player2Prereg->text(),player2id,errStr))
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
        if (!addPlayer(player3Name->text(),player3Character->text(),player3Origin->text(),player3Description->text(),player3Prereg->text(),3,errStr))
        {
            QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant 3. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    } else if (player3id != -1)
    {
        // update player 3
        if (!updatePlayer(player3Name->text(),player3Character->text(),player3Origin->text(),player3Description->text(),player3Prereg->text(),player3id,errStr))
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
        if (!addPlayer(player4Name->text(),player4Character->text(),player4Origin->text(),player4Description->text(),player4Prereg->text(),4,errStr))
        {
            QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant 4. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    } else if (player4id != -1)
    {
        // update player 4
        if (!updatePlayer(player4Name->text(),player4Character->text(),player4Origin->text(),player4Description->text(),player4Prereg->text(),player4id,errStr))
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
        if (!addPlayer(player5Name->text(),player5Character->text(),player5Origin->text(),player5Description->text(),player5Prereg->text(),5,errStr))
        {
            QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant 5. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    } else if (player5id != -1)
    {
        // update player 5
        if (!updatePlayer(player5Name->text(),player5Character->text(),player5Origin->text(),player5Description->text(),player5Prereg->text(),player5id,errStr))
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
        if (!addPlayer(player6Name->text(),player6Character->text(),player6Origin->text(),player6Description->text(),player6Prereg->text(),6,errStr))
        {
            QMessageBox::critical(this,"Unable to add contestant",QString("Unable to save contestant 6. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    } else if (player6id != -1)
    {
        // update player 6
        if (!updatePlayer(player6Name->text(),player6Character->text(),player6Origin->text(),player6Description->text(),player6Prereg->text(),player6id,errStr))
        {
            QMessageBox::critical(this,"Unable to update contestant",QString("Unable to save contestant 6. Error: %1").arg(errStr));
            db.rollback();
            return;
        }
    }--*/
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
    if (musicUrlChanged)
        addUpdateField(updateStringFields, updateStringValues, "music_url", musicUrl->text());

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
        else if (catChildren->isChecked())
            catID=6;
        addUpdateField(updateStringFields, updateStringValues, "category_id", QString("%1").arg(catID));
    }
    if (entryCommentsChanged)
        addUpdateField(updateStringFields, updateStringValues, "notes_entry", entryComments->toPlainText());
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
DialogModEntry::getPlayerName(QString& realName, QString& charName, QString& origin, QString& desc, QString& prereg, int player_id)
{
    QSqlQuery entryQuery;
    if (!entryQuery.exec(QString("SELECT real_name, character_name, origin, description, pre_reg from performer where id_player = %1").arg(player_id)))
    {
        QMessageBox::critical(this,"Unable to get entry's contestant info",QString("Unable to get entry's contestant info from database. Error: %1").arg(entryQuery.lastError().text()));
        return false;
    }
    if (entryQuery.next())
    {
        realName = entryQuery.record().value("real_name").toString();
        charName = entryQuery.record().value("character_name").toString();
        origin   = entryQuery.record().value("origin").toString();
        desc     = entryQuery.record().value("description").toString();
        prereg   = entryQuery.record().value("pre_reg").toString();
    } else
        return false;
    return true;
}

bool
DialogModEntry::addPlayer(QString name, QString character, QString origin, QString desc, QString prereg, int playerIndex, QString& errStr)
{
    QString sqlString;
    sqlString = "INSERT INTO performer (real_name";
    if (!character.isEmpty())
        sqlString.append(", character_name");
    if (!origin.isEmpty())
        sqlString.append(", origin");
    if (!desc.isEmpty())
        sqlString.append(", description");
    if (!prereg.isEmpty())
        sqlString.append(", pre_reg");
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
    if (!prereg.isEmpty())
    {
        sqlString.append(", '");
        sqlString.append(DBUtility::quote(prereg));
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
DialogModEntry::updatePlayer(QString name, QString character, QString origin, QString desc, QString prereg, int playerID, QString& errStr)
{
    QString sqlString;
    sqlString = "UPDATE performer SET (real_name, character_name, origin, description, pre_reg) = (";
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
        sqlString.append("', ");
    } else
    {
        sqlString.append("null, ");
    }
    if (!origin.isEmpty())
    {
        sqlString.append("'");
        sqlString.append(DBUtility::quote(origin));
        sqlString.append("', ");
    } else
    {
        sqlString.append("null, ");
    }
    if (!desc.isEmpty())
    {
        sqlString.append("'");
        sqlString.append(DBUtility::quote(desc));
        sqlString.append("', ");
    } else
    {
        sqlString.append("null, ");
    }
    if (!prereg.isEmpty())
    {
        sqlString.append("'");
        sqlString.append(DBUtility::quote(prereg));
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
    else if (sender() == musicUrl)
        musicUrlChanged = true;
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
    else if (sender() == announcerNotes)
        announcerNotesChanged=true;
    else if (sender() == soundNotes)
        soundNotesChanged=true;
}


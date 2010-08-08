#include <QtGui>

#include "MasterMain.h"
#include "MasterStatus.h"
#include "DialogNewEntry.h"
#include "DialogModEntry.h"
#include "DialogAddJudge.h"
#include "DialogGuestJudgeForm.h"

MasterMain::MasterMain(QWidget* parent)
          : QMainWindow(parent)
{
    MasterStatus* status = new MasterStatus();
    setCentralWidget(status);
    createActions();
    createMenus();
    createToolbar();
    setWindowTitle("Cosplay Contest Administration");
	setWindowIcon(QIcon(":/images/new_judge2.png"));

    dlgNewEntry = new DialogNewEntry(this);
    dlgModEntry = new DialogModEntry(this);
    connect(dlgNewEntry,SIGNAL(accepted()),this,SLOT(handleNewEntry()));
    connect(dlgNewEntry,SIGNAL(accepted()),dlgModEntry,SLOT(refresh()));
}

MasterMain::~MasterMain()
{
}

void
MasterMain::createActions()
{
	// app menu
    logoutAct = new QAction("Log&out", this);
	logoutAct->setShortcuts(QKeySequence::Close);
    connect(logoutAct, SIGNAL(triggered()), this, SLOT(logout()));
    exitAct = new QAction("E&xit", this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    // contest actions
    newEntryAct = new QAction(QIcon(":/images/new_entry.png"), "&New entry",this);
    newEntryAct->setShortcuts(QKeySequence::New);
    connect(newEntryAct, SIGNAL(triggered()), this, SLOT(newEntry()));
    modEntryAct = new QAction(QIcon(":/images/mod_entry.png"), "&Modify entry",this);
    connect(modEntryAct, SIGNAL(triggered()), this, SLOT(modEntry()));
    deleteEntryAct = new QAction(QIcon(":/images/remove_entry.png"), "&Delete entry",this);
    connect(deleteEntryAct, SIGNAL(triggered()), this, SLOT(deleteEntry()));
    showWaitListAct = new QAction(QIcon(":/images/wait_list.png"), "Show &wait list",this);
    connect(showWaitListAct, SIGNAL(triggered()), this, SLOT(showWaitList()));
    showGraveyardAct = new QAction(QIcon(":/images/graveyard.png"), "Show &graveyard",this);
    connect(showGraveyardAct, SIGNAL(triggered()), this, SLOT(showGraveyard()));

    // judge actions
    newJudgeAct = new QAction(QIcon(":/images/new_judge1.png"), "&New judge",this);
    connect(newJudgeAct, SIGNAL(triggered()), this, SLOT(newJudge()));
    modJudgeAct = new QAction("&Modify judge",this);
    connect(modJudgeAct, SIGNAL(triggered()), this, SLOT(modJudge()));
    deleteJudgeAct = new QAction("&Delete judge",this);
    connect(deleteJudgeAct, SIGNAL(triggered()), this, SLOT(deleteJudge()));

    // form actions
    showMasterFormAct = new QAction("Show master of ceremonies form",this);
    connect(showMasterFormAct, SIGNAL(triggered()), this, SLOT(showMasterForm()));
    showSoundFormAct = new QAction("Show sound operator form",this);
    connect(showSoundFormAct, SIGNAL(triggered()), this, SLOT(showSoundForm()));
    showGuestJudgeFormAct = new QAction("Show guest judge form",this);
    connect(showGuestJudgeFormAct, SIGNAL(triggered()), this, SLOT(showGuestJudgeForm()));

    // music actions
    setEntryMusicAct = new QAction("Set entry's music",this);
    connect(setEntryMusicAct, SIGNAL(triggered()), this, SLOT(setEntryMusic()));
    generateMusicListAct = new QAction("Generate list of music files",this);
    connect(generateMusicListAct, SIGNAL(triggered()), this, SLOT(generateMusicList()));

    // scores actions
    showResultsAct = new QAction("Show contest results",this);
    connect(showResultsAct, SIGNAL(triggered()), this, SLOT(showResultsAct()));
}

void
MasterMain::createMenus()
{
    appMenu = new QMenu("&Application",this);
	appMenu->addAction(logoutAct);
    appMenu->addAction(exitAct);

    entryMenu = new QMenu("&Entry",this);
    entryMenu->addAction(newEntryAct);
    entryMenu->addAction(modEntryAct);
    entryMenu->addAction(deleteEntryAct);

    judgeMenu = new QMenu("&Judge",this);
    judgeMenu->addAction(newJudgeAct);
    judgeMenu->addAction(modJudgeAct);
    judgeMenu->addAction(deleteJudgeAct);

    formsMenu = new QMenu("&Forms",this);
    formsMenu->addAction(showMasterFormAct);
    formsMenu->addAction(showSoundFormAct);
    formsMenu->addAction(showGuestJudgeFormAct);

    musicMenu = new QMenu("&Music",this);
    musicMenu->addAction(setEntryMusicAct);
    musicMenu->addAction(generateMusicListAct);

    scoresMenu = new QMenu("&Scores",this);
    scoresMenu->addAction(showResultsAct);
    //scoresMenu->addAction(reviewScoresAct);

    menuBar()->addMenu(appMenu);
    menuBar()->addMenu(entryMenu);
    menuBar()->addMenu(judgeMenu);
    menuBar()->addMenu(formsMenu);
    menuBar()->addMenu(musicMenu);
    menuBar()->addMenu(scoresMenu);
}

void
MasterMain::createToolbar()
{
    mainToolBar = addToolBar("Main");
	mainToolBar->setIconSize(QSize(48,48));
    mainToolBar->addAction(newEntryAct);
    mainToolBar->addAction(modEntryAct);
    mainToolBar->addAction(deleteEntryAct);
    mainToolBar->addAction(showWaitListAct);
    mainToolBar->addAction(showGraveyardAct);
}

void
MasterMain::logout()
{
	this->close();
	qobject_cast<QWidget *>(parent())->show();
}

void
MasterMain::newEntry()
{
    dlgNewEntry->clearDataFields();
	dlgNewEntry->show();
}

void
MasterMain::modEntry()
{
	dlgModEntry->show();
}

void
MasterMain::deleteEntry()
{
}

void
MasterMain::showWaitList()
{
}

void
MasterMain::showGraveyard()
{
}

void
MasterMain::newJudge()
{
    DialogAddJudge* dlg = new DialogAddJudge(this);
    dlg->exec();
    delete dlg;
}

void
MasterMain::modJudge()
{
}

void
MasterMain::deleteJudge()
{
}

void
MasterMain::showMasterForm()
{
}

void
MasterMain::showSoundForm()
{
}

void
MasterMain::showGuestJudgeForm()
{
    DialogGuestJudgeForm* dlg = new DialogGuestJudgeForm(this);
    dlg->exec();
    delete dlg;
}

void
MasterMain::setEntryMusic()
{
}

void
MasterMain::generateMusicList()
{
}

void
MasterMain::showResults()
{
}

/*void
MasterMain::reviewScoresAct()
{
}*/

void
MasterMain::handleNewEntry()
{
    //dlgModEntry->refresh();
}

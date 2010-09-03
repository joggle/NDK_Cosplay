#ifndef NDK_COSTUME_CONTEST_MASTERMAIN_H
#define NDK_COSTUME_CONTEST_MASTERMAIN_H

#include <QMainWindow>

class QAction;
class QMenu;
class QWidget;
class QToolBar;

class DialogNewEntry;
class DialogModEntry;
class DialogDeleteEntry;

class MasterMain : public QMainWindow
{
Q_OBJECT
public:
    MasterMain(QWidget* parent=0);
    ~MasterMain();
private slots:
    void newEntry();
    void modEntry();
    void deleteEntry();
    void showWaitList();
    void showGraveyard();
    void newJudge();
    void modJudge();
    void deleteJudge();
    void showMasterForm();
    void showSoundForm();
    void showGuestJudgeForm();
    void setEntryMusic();
    void generateMusicList();
    void showResults();
	void logout();
    void handleNewEntry();
private:
    void createActions();
    void createMenus();
    void createToolbar();

    // actions
    QAction* exitAct;
	QAction* logoutAct;
    QAction* newEntryAct;
    QAction* modEntryAct;
    QAction* deleteEntryAct;
    QAction* showWaitListAct;
    QAction* showGraveyardAct;
    QAction* newJudgeAct;
    QAction* modJudgeAct;
    QAction* deleteJudgeAct;
    QAction* showMasterFormAct;
    QAction* showSoundFormAct;
    QAction* showGuestJudgeFormAct;
    QAction* setEntryMusicAct;
    QAction* generateMusicListAct;
    QAction* showResultsAct;

    // menus
    QMenu*   appMenu;
    QMenu*   entryMenu;
    QMenu*   judgeMenu;
    QMenu*   formsMenu;
    QMenu*   musicMenu;
    QMenu*   scoresMenu;

    QToolBar* mainToolBar;

    // dialogs
    DialogNewEntry* dlgNewEntry;
    DialogModEntry* dlgModEntry;
    DialogDeleteEntry* dlgDeleteEntry;
};

#endif // NDK_COSTUME_CONTEST_MASTERMAIN_H

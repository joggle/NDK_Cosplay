#ifndef NDK_COSTUME_CONTEST_DIALOGMODENTRY_H
#define NDK_COSTUME_CONTEST_DIALOGMODENTRY_H

#include <QDialog>
#include <QString>

class QPushButton;
class QRadioButton;
class QCheckBox;
class QLineEdit;
class QTextEdit;

class QTableView;
class QSqlQueryModel;
class QModelIndex;
class QFormLayout;

class DialogModEntry : public QDialog
{
Q_OBJECT
public:
    DialogModEntry(QWidget* parent=0);
    ~DialogModEntry();
public slots:
    void accept();
    void reject();
    void refresh();
private slots:
    void showError();
    void entrySelected(const QModelIndex & index);
    void handleTextChanged(const QString&);
    void handleBtnToggle(bool);
    void handleTextEditChanged();
    void updateDescription();
    void handlePlayerDescBtn();
    /*void updatePlayer1Desc();
    void updatePlayer2Desc();
    void updatePlayer3Desc();
    void updatePlayer4Desc();
    void updatePlayer5Desc();
    void updatePlayer6Desc();*/
private:
    void updatePlayerDescription(int playerIndex);
    void loadSettings();
    void saveSettings();
    void updateEntry();
    bool getPlayerName(QString& realName, QString& charName, QString& origin, QString& desc, QString& prereg, int player_id);
    bool deletePerformer(int player_id, int playerIndex);
    bool addPlayer(QString name, QString character, QString origin, QString desc, QString prereg, int playerIndex, QString& errStr);
    bool updatePlayer(QString name, QString character, QString origin, QString desc, QString prereg, int playerID, QString& errStr);
    void addUpdateField(QString& updateStringFields, QString& updateStringValues, const QString& fieldName, const QString& fieldValue);
    void addPlayerLayout(int playerID, QFormLayout* mainLayout);

    QSqlQueryModel* summaryModelUnassigned;
    QSqlQueryModel* summaryModelBeginner;
    QSqlQueryModel* summaryModelIntermediate;
    QSqlQueryModel* summaryModelMaster;
    QSqlQueryModel* summaryModelSkit;
    QSqlQueryModel* summaryModelChildren;
    QTableView* summaryViewUnassigned;
    QTableView* summaryViewBeginner;
    QTableView* summaryViewIntermediate;
    QTableView* summaryViewMaster;
    QTableView* summaryViewSkit;
    QTableView* summaryViewChildren;

    QCheckBox* statusConfirmed;
    QCheckBox* craftFormSent;
    QCheckBox* craftFormReceived;
    QLineEdit* entryDescription;
    QLineEdit* groupName;
    QLineEdit* skitName;
    QLineEdit* groupEMail;
    QLineEdit* scriptUrl;
    QLineEdit* musicUrl;
    QCheckBox* craftmanship;
    QRadioButton* catNotSet;
    QRadioButton* catSkit;
    QRadioButton* catBeginner;
    QRadioButton* catIntermediate;
    QRadioButton* catMaster;
    QRadioButton* catChildren;
    QTextEdit* entryComments;
    QTextEdit* announcerNotes;
    QTextEdit* soundNotes;

    bool descriptionChanged;
    bool groupNameChanged;
    bool skitNameChanged;
    bool groupEMailChanged;
    bool scriptUrlChanged;
    bool musicUrlChanged;
    bool confirmedChanged;
    bool formSentChanged;
    bool formReceivedChanged;
    bool craftmanshipChanged;
    bool categoryChanged;
    bool entryCommentsChanged;
    bool announcerNotesChanged;
    bool soundNotesChanged;

    QLineEdit** playerName;
    QLineEdit** playerCharacter;
    QLineEdit** playerOrigin;
    QLineEdit** playerDescription;
    QLineEdit** playerPrereg;
    QPushButton** playerDescBtn;
    int playerId[6];

    /*QLineEdit* player1Name;
    QLineEdit* player1Character;
    QLineEdit* player1Origin;
    QLineEdit* player1Description;
    QLineEdit* player1Prereg;
    QLineEdit* player2Name;
    QLineEdit* player2Character;
    QLineEdit* player2Origin;
    QLineEdit* player2Prereg;
    QLineEdit* player2Description;
    QLineEdit* player3Name;
    QLineEdit* player3Character;
    QLineEdit* player3Origin;
    QLineEdit* player3Description;
    QLineEdit* player3Prereg;
    QLineEdit* player4Name;
    QLineEdit* player4Character;
    QLineEdit* player4Origin;
    QLineEdit* player4Description;
    QLineEdit* player4Prereg;
    QLineEdit* player5Name;
    QLineEdit* player5Character;
    QLineEdit* player5Origin;
    QLineEdit* player5Description;
    QLineEdit* player5Prereg;
    QLineEdit* player6Name;
    QLineEdit* player6Character;
    QLineEdit* player6Origin;
    QLineEdit* player6Description;
    QLineEdit* player6Prereg;

    QPushButton* player1DescBtn;
    QPushButton* player2DescBtn;
    QPushButton* player3DescBtn;
    QPushButton* player4DescBtn;
    QPushButton* player5DescBtn;
    QPushButton* player6DescBtn;*/

    bool selected_;
    /*int player1id;
    int player2id;
    int player3id;
    int player4id;
    int player5id;
    int player6id;*/
    int idEntry;
    int currentRow;
    bool breakFast;

    enum SelectedCategory
    {
        Unassigned,
        Beginner,
        Intermediate,
        Master,
        Skit,
        Children
    };
    SelectedCategory selectedCategory;
};

#endif // NDK_COSTUME_CONTEST_DIALOGMODENTRY_H

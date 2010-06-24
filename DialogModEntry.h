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
private:
    void loadSettings();
    void saveSettings();
    void updateEntry();
    bool getPlayerName(QString& realName, QString& charName, int player_id);
    bool deletePerformer(int player_id, int playerIndex);
    bool addPlayer(QString name, QString character, int playerIndex, QString& errStr);
    bool updatePlayer(QString name, QString character, int playerID, QString& errStr);
    void addUpdateField(QString& updateStringFields, QString& updateStringValues, const QString& fieldName, const QString& fieldValue);
    QSqlQueryModel* summaryModel;
    QTableView* summaryView;

    QCheckBox* statusConfirmed;
    QCheckBox* craftFormSent;
    QCheckBox* craftFormReceived;
    QLineEdit* entryDescription;
    QLineEdit* groupName;
    QLineEdit* skitName;
    QLineEdit* groupEMail;
    QLineEdit* scriptUrl;
    QCheckBox* craftmanship;
    QRadioButton* catNotSet;
    QRadioButton* catSkit;
    QRadioButton* catBeginner;
    QRadioButton* catIntermediate;
    QRadioButton* catMaster;
    QTextEdit* entryComments;
    QTextEdit* originComments;
    QTextEdit* announcerNotes;
    QTextEdit* soundNotes;

    bool descriptionChanged;
    bool groupNameChanged;
    bool skitNameChanged;
    bool groupEMailChanged;
    bool scriptUrlChanged;
    bool confirmedChanged;
    bool formSentChanged;
    bool formReceivedChanged;
    bool craftmanshipChanged;
    bool categoryChanged;
    bool entryCommentsChanged;
    bool originCommentsChanged;
    bool announcerNotesChanged;
    bool soundNotesChanged;

    QLineEdit* player1Name;
    QLineEdit* player1Character;
    QLineEdit* player1Prereg;
    QLineEdit* player2Name;
    QLineEdit* player2Character;
    QLineEdit* player2Prereg;
    QLineEdit* player3Name;
    QLineEdit* player3Character;
    QLineEdit* player3Prereg;
    QLineEdit* player4Name;
    QLineEdit* player4Character;
    QLineEdit* player4Prereg;
    QLineEdit* player5Name;
    QLineEdit* player5Character;
    QLineEdit* player5Prereg;
    QLineEdit* player6Name;
    QLineEdit* player6Character;
    QLineEdit* player6Prereg;

    bool selected_;
    int player1id;
    int player2id;
    int player3id;
    int player4id;
    int player5id;
    int player6id;
    int idEntry;
    int currentRow;
    bool breakFast;
};

#endif // NDK_COSTUME_CONTEST_DIALOGMODENTRY_H

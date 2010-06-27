#ifndef NDK_COSTUME_CONTEST_DIALOGNEWENTRY_H
#define NDK_COSTUME_CONTEST_DIALOGNEWENTRY_H

#include <QDialog>
#include <QString>

class QPushButton;
class QRadioButton;
class QCheckBox;
class QLineEdit;
class QTextEdit;

class DialogNewEntry : public QDialog
{
Q_OBJECT
public:
    DialogNewEntry(QWidget* parent=0);
    ~DialogNewEntry();
public slots:
    void accept();
    void reject();
private slots:
    void autoFillFields();
    void clearDataFields();
    void updateDescription();
    void updatePlayer1Desc();
    void updatePlayer2Desc();
    void updatePlayer3Desc();
    void updatePlayer4Desc();
    void updatePlayer5Desc();
    void updatePlayer6Desc();
private:
    void updatePlayerDescription(int playerIndex);
    void loadSettings();
    void saveSettings();
    bool addPlayer(QString name, QString character, QString origin, QString desc, int& playerID, QString& errStr);
    int getCategoryID();

    QTextEdit* webFormInfo;
    QPushButton* autoFill;
    QPushButton* clearData;
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
    //QTextEdit* originComments;
    QTextEdit* announcerNotes;
    QTextEdit* soundNotes;

    QLineEdit* player1Name;
    QLineEdit* player1Character;
    QLineEdit* player1Origin;
    QLineEdit* player1Description;
    QLineEdit* player2Name;
    QLineEdit* player2Character;
    QLineEdit* player2Origin;
    QLineEdit* player2Description;
    QLineEdit* player3Name;
    QLineEdit* player3Character;
    QLineEdit* player3Origin;
    QLineEdit* player3Description;
    QLineEdit* player4Name;
    QLineEdit* player4Character;
    QLineEdit* player4Origin;
    QLineEdit* player4Description;
    QLineEdit* player5Name;
    QLineEdit* player5Character;
    QLineEdit* player5Origin;
    QLineEdit* player5Description;
    QLineEdit* player6Name;
    QLineEdit* player6Character;
    QLineEdit* player6Origin;
    QLineEdit* player6Description;

    QPushButton* player1DescBtn;
    QPushButton* player2DescBtn;
    QPushButton* player3DescBtn;
    QPushButton* player4DescBtn;
    QPushButton* player5DescBtn;
    QPushButton* player6DescBtn;
};

#endif // NDK_COSTUME_CONTEST_DIALOGNEWENTRY_H

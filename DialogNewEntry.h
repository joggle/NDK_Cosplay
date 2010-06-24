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
private:
    void loadSettings();
    void saveSettings();
    bool addPlayer(QString name, QString character, int& playerID, QString& errStr);
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
    QTextEdit* originComments;
    QTextEdit* announcerNotes;
    QTextEdit* soundNotes;

    QLineEdit* player1Name;
    QLineEdit* player1Character;
    QLineEdit* player2Name;
    QLineEdit* player2Character;
    QLineEdit* player3Name;
    QLineEdit* player3Character;
    QLineEdit* player4Name;
    QLineEdit* player4Character;
    QLineEdit* player5Name;
    QLineEdit* player5Character;
    QLineEdit* player6Name;
    QLineEdit* player6Character;
};

#endif // NDK_COSTUME_CONTEST_DIALOGNEWENTRY_H

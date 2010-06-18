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
private:
    void loadSettings();
    void saveSettings();
    bool getPlayerName(QString& realName, QString& charName, int player_id);
    QSqlQueryModel* summaryModel;
    QTableView* summaryView;
    QLineEdit* entryDescription;
    QLineEdit* groupName;
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

#endif // NDK_COSTUME_CONTEST_DIALOGMODENTRY_H

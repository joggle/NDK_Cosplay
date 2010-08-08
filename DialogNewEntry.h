#ifndef NDK_COSTUME_CONTEST_DIALOGNEWENTRY_H
#define NDK_COSTUME_CONTEST_DIALOGNEWENTRY_H

#include <QDialog>
#include <QString>

class QPushButton;
class QRadioButton;
class QCheckBox;
class QLineEdit;
class QTextEdit;
class QFormLayout;

class DialogNewEntry : public QDialog
{
Q_OBJECT
public:
    DialogNewEntry(QWidget* parent=0);
    ~DialogNewEntry();
public slots:
    void accept();
    void reject();
    void clearDataFields();
private slots:
    void autoFillFields();
    void updateDescription();
    void handlePlayerDescBtn();
private:
    void updatePlayerDescription(int playerIndex);
    void loadSettings();
    void saveSettings();
    bool addPlayer(QString name, QString character, QString origin, QString desc, int& playerID, QString& errStr);
    int getCategoryID();
    void addPlayerLayout(int playerID, QFormLayout* mainLayout);

    QTextEdit* webFormInfo;
    QPushButton* autoFill;
    QPushButton* clearData;
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

    QLineEdit** playerName;
    QLineEdit** playerCharacter;
    QLineEdit** playerOrigin;
    QLineEdit** playerDescription;
    QPushButton** playerDescBtn;
};

#endif // NDK_COSTUME_CONTEST_DIALOGNEWENTRY_H

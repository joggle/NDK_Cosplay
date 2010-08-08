#ifndef NDK_COSTUME_CONTEST_DIALOGGUESTJUDGEFORM_H
#define NDK_COSTUME_CONTEST_DIALOGGUESTJUDGEFORM_H

#include <QDialog>
#include <QString>

class QTextEdit;
class QSqlQuery;

class DialogGuestJudgeForm : public QDialog
{
Q_OBJECT
public:
    DialogGuestJudgeForm(QWidget* parent=0);
    ~DialogGuestJudgeForm();
public slots:
    void print();
    void refresh();
protected slots:
    void accept();
private:
    void loadSettings();
    void saveSettings();
    bool getPlayerInfo(QString playerID, QString& description, QString& errStr);
    void addTable(QString& docText,QString title, QSqlQuery& query, bool isSkit=false);
    QTextEdit* form_;
};

#endif // NDK_COSTUME_CONTEST_DIALOGGUESTJUDGEFORM_H

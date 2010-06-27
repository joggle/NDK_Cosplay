#ifndef NDK_COSTUME_CONTEST_DIALOGADDJUDGE_H
#define NDK_COSTUME_CONTEST_DIALOGADDJUDGE_H

#include <QDialog>

class QLineEdit;

class DialogAddJudge : public QDialog
{
Q_OBJECT
public:
    DialogAddJudge(QWidget* parent=0);
    ~DialogAddJudge();
public slots:
    void accept();
private:
    bool addJudge();
    QLineEdit* judgeName_;
    QLineEdit* judgeUserName_;
    QLineEdit* judgePassword_;
};

#endif // NDK_COSTUME_CONTEST_DIALOGADDJUDGE_H

#ifndef NDK_COSTUME_CONTEST_DIALOGDELETEJUDGE_H
#define NDK_COSTUME_CONTEST_DIALOGDELETEJUDGE_H

#include <QDialog>

class QSqlQueryModel;
class QTableView;

class DialogDeleteJudge : public QDialog
{
Q_OBJECT
public:
    DialogDeleteJudge(QWidget* parent=0);
    ~DialogDeleteJudge();
public slots:
    void accept();
private:
    bool deleteJudge();
    QSqlQueryModel* judgeListModel;
    QTableView* judgeListView;
    //QLineEdit* judgeName_;
    //QLineEdit* judgeUserName_;
    //QLineEdit* judgePassword_;
};

#endif // NDK_COSTUME_CONTEST_DIALOGDELETEJUDGE_H

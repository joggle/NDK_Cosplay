#ifndef NDK_COSTUME_CONTEST_DIALOGACCESS_H
#define NDK_COSTUME_CONTEST_DIALOGACCESS_H

#include <QDialog>

class QLineEdit;

class DialogAccess : public QDialog
{
Q_OBJECT
public:
    DialogAccess();
    ~DialogAccess();
public slots:
    void accept();
private:
    QLineEdit* userName_;
    QLineEdit* userPassword_;
    QLineEdit* dbHost_;
    QLineEdit* dbPort_;
};

#endif // NDK_COSTUME_CONTEST_DIALOGACCESS_H

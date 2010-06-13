#ifndef NDK_COSTUME_CONTEST_MASTERMAIN_H
#define NDK_COSTUME_CONTEST_MASTERMAIN_H

#include <QWidget>

class QLineEdit;

class MasterMain : public QWidget
{
Q_OBJECT
public:
    MasterMain();
    ~MasterMain();
public slots:
    void accept();
private:
    QLineEdit* userName_;
    QLineEdit* userPassword_;
    QLineEdit* dbHost_;
    QLineEdit* dbPort_;
};

#endif // NDK_COSTUME_CONTEST_MASTERMAIN_H

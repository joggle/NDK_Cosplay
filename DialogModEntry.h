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
private:
    void loadSettings();
    void saveSettings();
    QSqlQueryModel* summaryModel;
    QTableView* summaryView;
};

#endif // NDK_COSTUME_CONTEST_DIALOGMODENTRY_H

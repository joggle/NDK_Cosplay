#ifndef NDK_COSTUME_CONTEST_DIALOGDELETEENTRY_H
#define NDK_COSTUME_CONTEST_DIALOGDELETEENTRY_H

#include <QDialog>

class QCheckBox;

class QTableView;
class QSqlQueryModel;

class DialogDeleteEntry : public QDialog
{
Q_OBJECT
public:
    DialogDeleteEntry(QWidget* parent=0);
    ~DialogDeleteEntry();
public slots:
    void accept();
    void reject();
    void refresh();
private slots:
    void loadSettings();
    void saveSettings();
    void deleteEntry();
private:
    QSqlQueryModel* modelEntry;
    QTableView* viewEntry;
    QCheckBox* permaDelete;
};

#endif // NDK_COSTUME_CONTEST_DIALOGDELETEENTRY_H

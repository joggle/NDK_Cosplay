#include <QtGui>
#include <QtSql>

#include "DialogDeleteJudge.h"

DialogDeleteJudge::DialogDeleteJudge(QWidget* parent)
                 : QDialog(parent)
{
}

DialogDeleteJudge::~DialogDeleteJudge()
{
}

void
DialogDeleteJudge::accept()
{
    if (deleteJudge())
        QDialog::accept();
}

bool
DialogDeleteJudge::deleteJudge()
{
    return true;
}


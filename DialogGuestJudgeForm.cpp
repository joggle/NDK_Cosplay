#include <QtGui>
#include <QtSql>

#include "DialogGuestJudgeForm.h"

DialogGuestJudgeForm::DialogGuestJudgeForm(QWidget* parent)
                    : QDialog(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    form_ = new QTextEdit();
    form_->document()->setDefaultStyleSheet("th { border-bottom: 2px solid; padding: 10px 8px; font-size: 20px; }\ntd { font-size: 20px };");
    mainLayout->addWidget(form_);
    QPushButton* printBtn = new QPushButton("Print");
    QPushButton* acceptBtn = new QPushButton("OK");
    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(printBtn);
    btnLayout->addStretch();
    btnLayout->addWidget(acceptBtn);
    mainLayout->addLayout(btnLayout);
    setLayout(mainLayout);
    connect(printBtn,SIGNAL(clicked()),this,SLOT(print()));
    connect(acceptBtn,SIGNAL(clicked()),this,SLOT(accept()));
    setWindowTitle("Guest judge form");
    loadSettings();
    refresh();
}

DialogGuestJudgeForm::~DialogGuestJudgeForm()
{
}

void
DialogGuestJudgeForm::accept()
{
    QDialog::accept();
    saveSettings();
}

void
DialogGuestJudgeForm::loadSettings()
{
    QSettings settings;
    settings.beginGroup("GuestJudgeFormDialog");
    resize(settings.value("size",QSize(520,671)).toSize());
    move(settings.value("pos",QPoint(200,200)).toPoint());
    settings.endGroup();
}

void
DialogGuestJudgeForm::saveSettings()
{
    QSettings settings;
    settings.beginGroup("GuestJudgeFormDialog");
    settings.setValue("size",size());
    settings.setValue("pos",pos());
    settings.endGroup();
}

void
DialogGuestJudgeForm::print()
{
}

void
DialogGuestJudgeForm::refresh()
{
    QSqlQuery guestQueryBeginner, guestQueryIntermediate, guestQueryMaster, guestQuerySkit;
    if (!guestQueryBeginner.exec("SELECT * from guest_entry_form WHERE category_id = 2"))
    {
        QMessageBox::critical(this,"Unable to get entry info",QString("Unable to get entry info from database. Error: %1").arg(guestQueryBeginner.lastError().text()));
        return;
    }
    if (!guestQueryIntermediate.exec("SELECT * from guest_entry_form WHERE category_id = 3"))
    {
        QMessageBox::critical(this,"Unable to get entry info",QString("Unable to get entry info from database. Error: %1").arg(guestQueryIntermediate.lastError().text()));
        return;
    }
    if (!guestQueryMaster.exec("SELECT * from guest_entry_form WHERE category_id = 4"))
    {
        QMessageBox::critical(this,"Unable to get entry info",QString("Unable to get entry info from database. Error: %1").arg(guestQueryMaster.lastError().text()));
        return;
    }
    if (!guestQuerySkit.exec("SELECT * from guest_entry_form WHERE category_id = 1"))
    {
        QMessageBox::critical(this,"Unable to get entry info",QString("Unable to get entry info from database. Error: %1").arg(guestQuerySkit.lastError().text()));
        return;
    }
    form_->clear();
    QString docText;
    docText.append("<h1>Please choose the order# you liked best to give your award to.</h1>\n");
    addTable(docText,"Beginner",guestQueryBeginner);
    addTable(docText,"Intermediate",guestQueryIntermediate);
    addTable(docText,"Master",guestQueryMaster);
    addTable(docText,"Skit",guestQuerySkit,true);
    form_->setHtml(docText);
}

void
DialogGuestJudgeForm::addTable(QString& docText,QString title, QSqlQuery& query, bool isSkit)
{
    docText.append(QString("<h1>%1</h1>\n").arg(title));
    docText.append("<table><tr><th align='left'>Order#</th><th align='left'>ID#</th><th align='left' width='50%'>Description</th><th align='left'>Notes</th></tr>\n");
    QString blankText("<u>");
    int ii;
    for (ii=0; ii < 60; ++ii)
        blankText.append("&nbsp;");
    blankText.append("</u>");
    while (query.next())
    {
        QString order = query.record().value("order").toString();
        QString id = query.record().value("id_entry").toString();
        if (isSkit)
        {
            QString description = query.record().value("description").toString();
            QString firstPart = QString("<tr><td>%1</td><td>%2</td>").arg(order).arg(id);
            docText.append(QString("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td></tr>\n").arg(order).arg(id).arg(description).arg(blankText));
        } else
        {
            QString description, errStr;
            QString player_1_id, player_2_id, player_3_id, player_4_id, player_5_id, player_6_id;
            player_1_id = query.record().value("player_1_id").toString();
            if (!query.record().isNull("player_2_id"))
                player_2_id = query.record().value("player_2_id").toString();
            if (!query.record().isNull("player_3_id"))
                player_3_id = query.record().value("player_3_id").toString();
            if (!query.record().isNull("player_4_id"))
                player_4_id = query.record().value("player_4_id").toString();
            if (!query.record().isNull("player_5_id"))
                player_5_id = query.record().value("player_5_id").toString();
            if (!query.record().isNull("player_6_id"))
                player_6_id = query.record().value("player_6_id").toString();
            /*qWarning("id=%s, player_1_id=%s, player_2_id=%s, player_3_id=%s, player_4_id=%s, player_5_id=%s, player_6_id=%s",
                qPrintable(id),
                qPrintable(player_1_id),
                qPrintable(player_2_id),
                qPrintable(player_3_id),
                qPrintable(player_4_id),
                qPrintable(player_5_id),
                qPrintable(player_6_id));*/
            QString firstPart = QString("<tr><td>%1</td><td>%2</td>").arg(order).arg(id);
            // player 1
            if (!getPlayerInfo(player_1_id,description,errStr))
            {
                QMessageBox::critical(this,"Unable to get entry info",QString("Unable to get entry info from database. Error: %1").arg(errStr));
                return;
            }
            docText.append(QString("%1<td>%2</td><td>%3</td></tr>\n").arg(firstPart).arg(description).arg(blankText));
            // player 2
            if (!player_2_id.isEmpty())
            {
                if (!getPlayerInfo(player_2_id,description,errStr))
                {
                    QMessageBox::critical(this,"Unable to get entry info",QString("Unable to get entry info from database. Error: %1").arg(errStr));
                    return;
                }
                docText.append(QString("%1<td>%2</td><td>%3</td></tr>\n").arg(firstPart).arg(description).arg(blankText));
            }
            // player 3
            if (!player_3_id.isEmpty())
            {
                if (!getPlayerInfo(player_3_id,description,errStr))
                {
                    QMessageBox::critical(this,"Unable to get entry info",QString("Unable to get entry info from database. Error: %1").arg(errStr));
                    return;
                }
                docText.append(QString("%1<td>%2</td><td>%3</td></tr>\n").arg(firstPart).arg(description).arg(blankText));
            }
            // player 4
            if (!player_4_id.isEmpty())
            {
                if (!getPlayerInfo(player_4_id,description,errStr))
                {
                    QMessageBox::critical(this,"Unable to get entry info",QString("Unable to get entry info from database. Error: %1").arg(errStr));
                    return;
                }
                docText.append(QString("%1<td>%2</td><td>%3</td></tr>\n").arg(firstPart).arg(description).arg(blankText));
            }
            // player 5
            if (!player_5_id.isEmpty())
            {
                if (!getPlayerInfo(player_5_id,description,errStr))
                {
                    QMessageBox::critical(this,"Unable to get entry info",QString("Unable to get entry info from database. Error: %1").arg(errStr));
                    return;
                }
                docText.append(QString("%1<td>%2</td><td>%3</td></tr>\n").arg(firstPart).arg(description).arg(blankText));
            }
            // player 6
            if (!player_6_id.isEmpty())
            {
                if (!getPlayerInfo(player_6_id,description,errStr))
                {
                    QMessageBox::critical(this,"Unable to get entry info",QString("Unable to get entry info from database. Error: %1").arg(errStr));
                    return;
                }
                docText.append(QString("%1<td>%2</td><td>%3</td></tr>\n").arg(firstPart).arg(description).arg(blankText));
            }
        } // if !isSkit
    } // for each entry in this category
    docText.append("</table>");
}

bool
DialogGuestJudgeForm::getPlayerInfo(QString playerID, QString& description, QString& errStr)
{
    QSqlQuery playerQuery;
    if (!playerQuery.exec(QString("SELECT description FROM performer WHERE id_player = %1").arg(playerID)))
    {
        errStr = playerQuery.lastError().text();
        return false;
    }
    if (playerQuery.next())
        description = playerQuery.record().value("description").toString();
    else
    {
        errStr = "No matching player ID";
        return false;
    }
    return true;
}

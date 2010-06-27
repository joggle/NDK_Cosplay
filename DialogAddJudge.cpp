#include <QtGui>
#include <QtSql>

#include "DialogAddJudge.h"
#include "DBUtility.h"

DialogAddJudge::DialogAddJudge(QWidget* parent)
              : QDialog(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QFormLayout* judgeLayout = new QFormLayout();
    judgeName_ = new QLineEdit();
    judgeLayout->addRow("Judge name:",judgeName_);
    judgeUserName_ = new QLineEdit();
    judgeLayout->addRow("User name:",judgeUserName_);
    judgePassword_ = new QLineEdit();
    judgeLayout->addRow("Password:",judgePassword_);
    mainLayout->addLayout(judgeLayout);
    QDialogButtonBox* buttonBox = new QDialogButtonBox();
    buttonBox->addButton(QDialogButtonBox::Save);
    buttonBox->addButton(QDialogButtonBox::Cancel);
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
    connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    setWindowTitle("Add new judge");
}

DialogAddJudge::~DialogAddJudge()
{
}

void
DialogAddJudge::accept()
{
    if (addJudge())
        QDialog::accept();
}

bool
DialogAddJudge::addJudge()
{
    QString name = judgeName_->text();
    QString userName = judgeUserName_->text();
    QString pwd = judgePassword_->text();
    if (name.isEmpty())
    {
        QMessageBox::warning(this,"Unable to create judge","Unable to create judge because the judge's name hasn't been set.");
        return false;
    }
    if (userName.isEmpty())
    {
        QMessageBox::warning(this,"Unable to create judge","Unable to create judge because the judge's user name hasn't been set.");
        return false;
    }
    if (pwd.isEmpty())
    {
        QMessageBox::warning(this,"Unable to create judge","Unable to create judge because the judge's password hasn't been set.");
        return false;
    }
    QSqlDatabase db(QSqlDatabase::database());
    if (!db.transaction())
    {
        QMessageBox::critical(this,"Unable to start transaction",QString("Unable to start database transaction. Error: %1").arg(db.lastError().text()));
        return false;
    }
    QString sqlString;
    sqlString = QString("CREATE ROLE %1 WITH LOGIN PASSWORD '%2'").arg(DBUtility::quote(userName)).arg(DBUtility::quote(pwd));
    QSqlQuery createRoleQuery;
    if (!createRoleQuery.exec(sqlString))
    {
        QMessageBox::critical(this,"Unable to create judge",QString("Unable to create new judge role. Error: %1").arg(createRoleQuery.lastError().text()));
        db.rollback();
        return false;
    }
    // add judge to list of judges to get their ID
    int judgeID;
    QSqlQuery addJudgeQuery;
    if (addJudgeQuery.exec(QString("INSERT INTO judge (name) VALUES ('%1') RETURNING id_judge").arg(DBUtility::quote(name))))
    {
        if (addJudgeQuery.next())
        {
            int fieldNo = addJudgeQuery.record().indexOf("id_judge");
            judgeID = addJudgeQuery.value(fieldNo).toInt();
        }
    } else
    {
        QMessageBox::critical(this,"Unable to create judge",QString("Unable to add judge to list of judges. Error: %1").arg(addJudgeQuery.lastError().text()));
        db.rollback();
        return false;
    }
    // create the judge's schema
    QSqlQuery createSchema, alterTable, alterTable2, addJudgeID, alterTable3;
    QString createSchemaStr;
    createSchemaStr = QString("CREATE SCHEMA %1 CREATE TABLE scores_craftmanship (CONSTRAINT pk_craftmanship PRIMARY KEY (id_craftmanship)) INHERITS (scores_craftmanship)").arg(userName);
    createSchemaStr.append(" CREATE TABLE scores_performance (CONSTRAINT pk_performance PRIMARY KEY (id_performance)) INHERITS (scores_performance)");
    createSchemaStr.append(" CREATE TABLE judge_id (id integer)");
    if (!createSchema.exec(createSchemaStr))
    {
        QMessageBox::critical(this,"Unable to create judge",QString("Unable to create judge's schema. Error: %1").arg(createSchema.lastError().text()));
        db.rollback();
        return false;
    }
    if (!alterTable.exec(QString("ALTER TABLE %1.scores_craftmanship OWNER TO %1").arg(userName)))
    {
        QMessageBox::critical(this,"Unable to create judge",QString("Unable to change onwer of scores_craftmanship to new judge. Error: %1").arg(alterTable.lastError().text()));
        db.rollback();
        return false;
    }
    if (!alterTable2.exec(QString("ALTER TABLE %1.scores_performance OWNER TO %1").arg(userName)))
    {
        QMessageBox::critical(this,"Unable to create judge",QString("Unable to change onwer of scores_performance to new judge. Error: %1").arg(alterTable2.lastError().text()));
        db.rollback();
        return false;
    }
    if (!addJudgeID.exec(QString("INSERT INTO %1.judge_id VALUES (%2)").arg(userName).arg(judgeID)))
    {
        QMessageBox::critical(this,"Unable to create judge",QString("Unable to add judge ID. Error: %1").arg(addJudgeID.lastError().text()));
        db.rollback();
        return false;
    }
    if (!alterTable3.exec(QString("ALTER TABLE %1.judge_id OWNER TO %1").arg(userName)))
    {
        QMessageBox::critical(this,"Unable to create judge",QString("Unable to change onwer of judge_id to new judge. Error: %1").arg(alterTable3.lastError().text()));
        db.rollback();
        return false;
    }
    if (!db.commit())
    {
        QMessageBox::critical(this,"Unable to update",QString("Unable to coomit to NDK costume contest database. Error: %1").arg(db.lastError().text()));
        return false;
    }
    return true;
}

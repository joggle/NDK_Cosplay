#include <QtGui>
#include <QtSql>

#include "DialogAccess.h"
#include "MasterMain.h"

DialogAccess::DialogAccess()
{
    QSettings settings;
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QFormLayout* userLayout = new QFormLayout();
    QFormLayout* dbLayout = new QFormLayout();
    QGroupBox* userBox = new QGroupBox("Login information");
    QGroupBox* dbBox = new QGroupBox("Database connection information");
    userName_ = new QLineEdit();
    userPassword_ = new QLineEdit();
    userPassword_->setEchoMode(QLineEdit::Password);
    userLayout->addRow("Login name:",userName_);
    userLayout->addRow("Password:",userPassword_);
    userBox->setLayout(userLayout);
    mainLayout->addWidget(userBox);
    dbHost_ = new QLineEdit();
    dbPort_ = new QLineEdit();
    dbPort_->setValidator(new QIntValidator(1024,65535,this));
    dbHost_->setText(settings.value("db/host","localhost").toString());
    dbPort_->setText(settings.value("db/port","5432").toString());
    dbLayout->addRow("Database host:",dbHost_);
    dbLayout->addRow("Database port:",dbPort_);
    dbBox->setLayout(dbLayout);
    mainLayout->addWidget(dbBox);
    QDialogButtonBox* buttonBox = new QDialogButtonBox();
    buttonBox->addButton(QDialogButtonBox::Ok);
    buttonBox->addButton(QDialogButtonBox::Cancel);
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
    connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    setWindowTitle("NDK Costume Contest Login");
}

DialogAccess::~DialogAccess()
{
}

void
DialogAccess::accept()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
	db.setHostName(dbHost_->text());
	db.setPort(dbPort_->text().toInt());
	db.setUserName(userName_->text());
	db.setPassword(userPassword_->text());
	db.setDatabaseName("ndk_cosplay");
	bool ok = db.open();
	if (!ok)
	{
		QMessageBox::critical(this,"Unable to connect",QString("Unable to connect to NDK costume contest database. Error: %1").arg(db.lastError().text()));
	} else
	{
		// see if we can select from results table
		QSqlQuery query;
        if (query.exec("SELECT id_result FROM results"))
		{
			// show the administration window
			MasterMain* adminMain = new MasterMain(this);
			this->hide();
			adminMain->show();
		} else
		{
			QMessageBox::information(this,"Cannot read from results",QString("Could not select rows from results table. Error: %1").arg(query.lastError().text()));
		}
	}
}

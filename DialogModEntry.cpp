#include <QtGui>
#include <QtSql>

#include "DialogModEntry.h"

DialogModEntry::DialogModEntry(QWidget* parent)
              : QDialog(parent)
{
    setWindowIcon(QIcon(":/images/mod_entry.png"));
    setWindowTitle("Modify entry");

    summaryModel = new QSqlQueryModel();
    summaryModel->setQuery("SELECT * FROM mod_entry_summary");
    summaryModel->setHeaderData(0, Qt::Horizontal, tr("Order"));
    summaryModel->setHeaderData(1, Qt::Horizontal, tr("Group"));
    summaryModel->setHeaderData(2, Qt::Horizontal, tr("Real name 1"));

    summaryView = new QTableView();
    summaryView->setModel(summaryModel);
    summaryView->show();
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(summaryView);
    setLayout(mainLayout);
    loadSettings();
    //QTimer::singleShot(200,this,SLOT(showError()));
}

DialogModEntry::~DialogModEntry()
{
}

void
DialogModEntry::showError()
{
    //QMessageBox::information(this,"Error?",QString("Last DB error: %1").arg(summaryModel->lastError().text()));
}

void
DialogModEntry::accept()
{
}

void
DialogModEntry::reject()
{
}

void
DialogModEntry::loadSettings()
{
    QSettings settings;
    settings.beginGroup("ModEntryDialog");
    resize(settings.value("size",QSize(520,671)).toSize());
    move(settings.value("pos",QPoint(200,200)).toPoint());
}

void
DialogModEntry::saveSettings()
{
    QSettings settings;
    settings.beginGroup("ModEntryDialog");
    settings.setValue("size",size());
    settings.setValue("pos",pos());
    settings.endGroup();
}

void
DialogModEntry::refresh()
{
    summaryModel->setQuery("SELECT * FROM mod_entry_summary");
}


#include <QtGui>
#include <QtSql>

#include "DialogDeleteEntry.h"
#include "DBUtility.h"

DialogDeleteEntry::DialogDeleteEntry(QWidget* parent)
                 : QDialog(parent)
{
    setWindowIcon(QIcon(":/images/remove_entry.png"));
    setWindowTitle("Remove entry");

    QVBoxLayout* mainLayout = new QVBoxLayout();

    modelEntry = new QSqlQueryModel();
    modelEntry->setQuery("SELECT group_name, real_name, id_entry, category.name, active_entries.entry_id FROM mod_entry_summary, category, active_entries WHERE category.category_id = mod_entry_summary.category_id AND id_entry = active_entries.entry_id");
    //summaryModelUnassigned->setHeaderData(0, Qt::Horizontal, tr("Order"));
    modelEntry->setHeaderData(0, Qt::Horizontal, tr("Group"));
    modelEntry->setHeaderData(1, Qt::Horizontal, tr("Real name 1"));
    modelEntry->setHeaderData(3, Qt::Horizontal, tr("Category"));

    viewEntry = new QTableView();
    //connect(summaryViewUnassigned,SIGNAL(clicked(const QModelIndex&)),this,SLOT(entrySelected(const QModelIndex&)));
    viewEntry->setModel(modelEntry);
    //summaryViewUnassigned->setColumnHidden(0,true);
    viewEntry->setColumnHidden(2,true);
    //summaryViewUnassigned->setColumnHidden(4,true);
    viewEntry->show();
    //summaryViewUnassigned->setMaximumWidth(400);
    mainLayout->addWidget(viewEntry);
    permaDelete = new QCheckBox("Delete permanently?");
    mainLayout->addWidget(permaDelete);
    QPushButton* delButton = new QPushButton(QIcon(":/images/graveyard2.png"),"Delete entry");
    delButton->setIconSize(QSize(48,48));
    delButton->setToolTip("Delete the entry.");
    connect(delButton,SIGNAL(clicked()),this,SLOT(deleteEntry()));
    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(delButton);
    btnLayout->addStretch();
    mainLayout->addLayout(btnLayout);

    QDialogButtonBox* buttonBox = new QDialogButtonBox();
    buttonBox->addButton(QDialogButtonBox::Close);
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
    connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    loadSettings();
}

DialogDeleteEntry::~DialogDeleteEntry()
{
}

void
DialogDeleteEntry::deleteEntry()
{
    int iRow = viewEntry->currentIndex().row();
    QSqlRecord entry = modelEntry->record(iRow);
    int idEntry = entry.value("id_entry").toInt();
    if (permaDelete->isChecked())
    {
        if (QMessageBox::question(this,"Delete permanently?","Are you sure you want to permanently delete this entry? All information for this entry will be lost.",
            QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            //QString sqlString;
            //sqlString = QString("CREATE ROLE %1 WITH LOGIN PASSWORD '%2'").arg(DBUtility::quote(userName)).arg(DBUtility::quote(pwd));
            qDebug("Would delete the entry %d (permanent)",idEntry);
        }
    } else
    {
        if (QMessageBox::question(this,"Send to graveyard?","Are you sure you want to send this entry to the graveyard?",
            QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            qDebug("Would send the entry %d to the graveyard",idEntry);
            QString sqlString = QString("DELETE FROM active_entries WHERE entry_id = %1").arg(idEntry);
            qDebug("%s\n",qPrintable(sqlString));
        }
    }
}

void
DialogDeleteEntry::accept()
{
    saveSettings();
    //if (selected_)
        //updateEntry();
    QDialog::accept();
}

void
DialogDeleteEntry::reject()
{
    saveSettings();
    QDialog::reject();
}

void
DialogDeleteEntry::loadSettings()
{
    QSettings settings;
    settings.beginGroup("DeleteEntryDialog");
    resize(settings.value("size",QSize(520,671)).toSize());
    move(settings.value("pos",QPoint(200,200)).toPoint());
    /*int sectSize = settings.value("w_0",-1).toInt();
    if (sectSize != -1)
    {
        summaryViewUnassigned->horizontalHeader()->resizeSection(0,sectSize);
        summaryViewBeginner->horizontalHeader()->resizeSection(0,sectSize);
        summaryViewIntermediate->horizontalHeader()->resizeSection(0,sectSize);
        summaryViewMaster->horizontalHeader()->resizeSection(0,sectSize);
        summaryViewSkit->horizontalHeader()->resizeSection(0,sectSize);
        summaryViewChildren->horizontalHeader()->resizeSection(0,sectSize);
    }
    sectSize = settings.value("w_1",-1).toInt();
    if (sectSize != -1)
    {
        summaryViewUnassigned->horizontalHeader()->resizeSection(1,sectSize);
        summaryViewBeginner->horizontalHeader()->resizeSection(1,sectSize);
        summaryViewIntermediate->horizontalHeader()->resizeSection(1,sectSize);
        summaryViewMaster->horizontalHeader()->resizeSection(1,sectSize);
        summaryViewSkit->horizontalHeader()->resizeSection(1,sectSize);
        summaryViewChildren->horizontalHeader()->resizeSection(1,sectSize);
    }
    sectSize = settings.value("w_2",-1).toInt();
    if (sectSize != -1)
    {
        summaryViewUnassigned->horizontalHeader()->resizeSection(2,sectSize);
        summaryViewBeginner->horizontalHeader()->resizeSection(2,sectSize);
        summaryViewIntermediate->horizontalHeader()->resizeSection(2,sectSize);
        summaryViewMaster->horizontalHeader()->resizeSection(2,sectSize);
        summaryViewSkit->horizontalHeader()->resizeSection(2,sectSize);
        summaryViewChildren->horizontalHeader()->resizeSection(2,sectSize);
    }*/
}

void
DialogDeleteEntry::saveSettings()
{
    QSettings settings;
    settings.beginGroup("DeleteEntryDialog");
    settings.setValue("size",size());
    settings.setValue("pos",pos());
    //settings.setValue("w_0",summaryViewUnassigned->horizontalHeader()->sectionSize(0));
    //settings.setValue("w_1",summaryViewUnassigned->horizontalHeader()->sectionSize(1));
    //settings.setValue("w_2",summaryViewUnassigned->horizontalHeader()->sectionSize(2));
    settings.endGroup();
}

void
DialogDeleteEntry::refresh()
{
    modelEntry->setQuery("SELECT group_name, real_name, id_entry, category.name FROM mod_entry_summary, category WHERE category.category_id = mod_entry_summary.category_id");
}


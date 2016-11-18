#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    connect(ui->comboBox_typeDB, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(DbChanged(QString)));
    connect(ui->pushButton_OpenSqlite, SIGNAL(clicked()),
            this, SLOT(SelectSQLiteDB()));
    connect(ui->pushButton_CreateSQLite, SIGNAL(clicked()),
            this, SLOT(CreateSQLiteDB()));
    connect(ui->pushButton_connect, SIGNAL(clicked()),
            this, SLOT(CheckSqlConnect()));
    connect(ui->pushButton_createTable, SIGNAL(clicked()),
            this, SLOT(CreateSqlTable()));

    ReadParameters();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::DbChanged(QString type)
{
    if (type.compare(ui->comboBox_typeDB->itemText(0)) == 0)
    {
        ui->tab_Sqlite->setEnabled(true);
        ui->tab_Sql->setEnabled(false);
    } else if (type.compare(ui->comboBox_typeDB->itemText(1)) == 0)
    {
        ui->tab_Sqlite->setEnabled(false);
        ui->tab_Sql->setEnabled(true);
    }
}

bool SettingsDialog::SaveParameters()
{
    Settings settings;
    if (ui->comboBox_typeDB->currentText() == "SQLite")
    {
        // Vérification du chemin de la base de données
        if (!QFile::exists(ui->lineEdit_PathSqlite->text()))
            return false;

        settings.setConnexion("QSQLITE");
        settings.setDbName(ui->lineEdit_PathSqlite->text());
    } else
    {
        // Detections des différents types à implémenter
        settings.setConnexion("QMYSQL");
        settings.setDbName(ui->lineEdit_dbNAme->text());
    }

    settings.setHost(ui->lineEdit_host->text());
    settings.setPort(ui->spinBox_Port->value());
    settings.setUser(ui->lineEdit_user->text());
    settings.setPassword(ui->lineEdit_pass->text());
    return true;
}

void SettingsDialog::ReadParameters()
{
    Settings settings;
    if (settings.getConnexion() == "QSQLITE")
    {
        ui->comboBox_typeDB->setCurrentIndex(0);
        ui->lineEdit_PathSqlite->setText(settings.getDbName());
    } else
    {
        ui->comboBox_typeDB->setCurrentIndex(1);
        ui->lineEdit_dbNAme->setText(settings.getDbName());
    }
    ui->lineEdit_host->setText(settings.getHost());
    ui->spinBox_Port->setValue(settings.getPort());
    ui->lineEdit_pass->setText(settings.getPassword());
    ui->lineEdit_user->setText(settings.getUser());
}

void SettingsDialog::SelectSQLiteDB()
{
    QString filename = QDir::homePath() + "/Softtech.xdata";

    // Affiche la fenetre pour ouvrir un fichier
    filename = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", filename, "Fichier Softtech(*.xdata)");
    ui->lineEdit_PathSqlite->setText(filename);
}

void SettingsDialog::CreateSQLiteDB()
{
    // Selectionne le repertoire personnel par defaut et le nom Softtech pour le fichier
    QString fileName = QDir::homePath() + "/Softtech.xdata";

    // Affiche la fenetre pour enregistrer un fichier
    fileName = QFileDialog::getSaveFileName(this, tr("Création d'une nouvelle base de données locale"), fileName, "Fichier Softtech(*.xdata)");
    if (fileName.isEmpty())
            return ;

    if (!Database::CreateSQLiteDB(fileName))
        QMessageBox::critical(0, tr("Création de la base de données locale"),
                              tr("Une erreur est survenue lors de la création de la base de données locale."));

    ui->lineEdit_PathSqlite->setText(fileName);//*/

    // creation des tables
}

void SettingsDialog::CheckSqlConnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(ui->lineEdit_host->text());
    db.setDatabaseName(ui->lineEdit_dbNAme->text());
    db.setPort(ui->spinBox_Port->value());
    db.setUserName(ui->lineEdit_user->text());
    db.setPassword(ui->lineEdit_pass->text());

    if (db.isValid())
        ui->pushButton_createTable->setEnabled(true);
    else
        ui->pushButton_createTable->setEnabled(false);
}

void SettingsDialog::CreateSqlTable()
{
    //TODO: gérer l'erreur possible lors de la creation
    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
        Database::CreateSQLiteDB(ui->lineEdit_PathSqlite->text());
    else
        QMessageBox::critical(0, tr("Erreur base de données"), db.lastError().text());
}

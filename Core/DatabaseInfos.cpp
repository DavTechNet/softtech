#include "DatabaseInfos.h"

DatabaseInfos::DatabaseInfos(QObject *parent) :
    QObject(parent)
{
    // Recupere la connexion existante
    QSqlDatabase db(QSqlDatabase::database());

    // Recuperation des informations de connexions

}

QSqlDatabase DatabaseInfos::SettingsInformations()
{
    Settings settings;
    QSqlDatabase base(QSqlDatabase::addDatabase(settings.getConnexion()));
    base.setDatabaseName(settings.getDbName());
    base.setHostName(settings.getHost());
    base.setUserName(settings.getUser());
    base.setPassword(settings.getPassword());
    base.setPort(settings.getPort());

    return base;
}

bool DatabaseInfos::ParameterExist()
{
    Settings settings;
    QString connexion = settings.getConnexion();
    if (connexion.isEmpty())
        return false;
    else
    {
        if ((connexion == "QDB2") || (connexion == "QIBASE") || (connexion == "QMYSQL") || (connexion == "QOCI")
                || (connexion == "QPSQL") || (connexion == "QODBC") || (connexion == "QSQLITE")
                || (connexion == "QSQLITE2") || (connexion == "QTDS"))
        return true;
        else
            return false;
    }
}

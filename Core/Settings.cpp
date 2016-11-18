
/*!
 * \file ./Core/Settings.cpp
 * \brief Gestion et sauvegarde des options
 * \author Florian Davin
 * \version 0.1
 */

#include "Settings.h"

/*!
 *  \brief Constructeur
 *
 *  Constructeur de la classe Settings
 *
 *  \param *parent : classe parente
 */
Settings::Settings(QObject *parent) :
    QSettings(parent)
{
    this->m_organization = "Perso";
    this->m_application  = "Softtech";
    settings = new QSettings(m_organization, m_application);
}

/*!
 *  \brief Destructeur
 *
 *  Destructeur de la classe Settings
 */
Settings::~Settings()
{
    delete settings;
}

/*!
 *  \brief Recuperation du type de base de donnees
 *
 *  Methode qui permet de savoir quel driver utiliser pour
 *  la connexion a la base de donnees
 *
 *  \return le nom du driver a charger
 */
QString Settings::getConnexion()
{
    settings->beginGroup("SQL");
    QString Connexion = settings->value("Connexion").toString();
    settings->endGroup();
    return Connexion;
}

/*!
 *  \brief Recuperation du nom de la base de donnees
 *
 *  Methode qui permet de connaitre le nom de
 *  la base de donnees a utiliser
 *
 *  \return le nom de la base de donnees
 */
QString Settings::getDbName()
{
    settings->beginGroup("SQL");
    QString name = settings->value("DB_name").toString();
    settings->endGroup();
    return name;
}

/*!
 *  \brief Recuperation de l'hote hebergeant la base de donnees
 *
 *  Methode qui permet de connaitre l'hote de connexion a
 *  la base de donnees
 *
 *  \return l'hote de la base de donnees
 */
QString Settings::getHost()
{
    settings->beginGroup("SQL");
    QString host = settings->value("Hote").toString();
    settings->endGroup();
    return host;
}

/*!
 *  \brief Recuperation du port de connexion a la base de donnees
 *
 *  Methode qui permet de connaitre le numero du port de connexion a
 *  la base de donnees
 *
 *  \return le numero du port
 */
int Settings::getPort()
{
    settings->beginGroup("SQL");
    int port = settings->value("Port").toInt();
    settings->endGroup();
    return port;
}

/*!
 *  \brief Recuperation de l'utilisateur
 *
 *  Methode qui permet de connaitre le nom de
 *  l'utilisateur pour se connecter  a la base de donnees
 *
 *  \return le nom d'utilisateur
 */
QString Settings::getUser()
{
    settings->beginGroup("SQL");
    QString user = settings->value("User").toString();
    settings->endGroup();
    return user;
}

/*!
 *  \brief Recuperation du mot de passe de l'utilisateur
 *
 *  Methode qui permet de recuperer le mot de passe enregistre
 *  a utiliser avec l'utilisateur pour la connexion a la base de donnees
 *
 *  \return le mot de passe enregistrer
 */
QString Settings::getPassword()
{
    settings->beginGroup("SQL");
    QString pass = settings->value("Password").toString();
    settings->endGroup();
    return pass;
}

/*!
 *  \brief Modification du type de base de donnees
 *
 *  Methode qui permet de changer le driver a utiliser pour
 *  la connexion a la base de donnees
 *
 *  \param connexion : le nom du driver a charger
 */
void Settings::setConnexion(QString connexion)
{
    settings->beginGroup("SQL");
    settings->setValue("Connexion", connexion);
    settings->endGroup();
}

/*!
 *  \brief Modification du nom de la base de donnees
 *
 *  Methode qui permet de connaitre le nom de
 *  la base de donnees a utiliser
 *
 *  \param dbName : le nom de la base de donnees
 */
void Settings::setDbName(QString dbName)
{
    settings->beginGroup("SQL");
    settings->setValue("DB_name", dbName);
    settings->endGroup();
}

/*!
 *  \brief Modification de l'hote hebergeant la base de donnees
 *
 *  Methode qui permet de modifier l'hote de connexion a
 *  la base de donnees
 *
 *  \param host : l'hote de la base de donnees
 */
void Settings::setHost(QString host)
{
    settings->beginGroup("SQL");
    settings->setValue("Hote", host);
    settings->endGroup();
}

/*!
 *  \brief Modification du port de connexion a la base de donnees
 *
 *  Methode qui permet de modifier le numero du port de connexion a
 *  la base de donnees
 *
 *  \param port : le numero du port a utiliser
 */
void Settings::setPort(int port)
{
    settings->beginGroup("SQL");
    settings->setValue("Port", port);
    settings->endGroup();
}

/*!
 *  \brief Modification de l'utilisateur
 *
 *  Methode qui permet de modifier le nom de
 *  l'utilisateur pour se connecter  a la base de donnees
 *
 *  \param user : le nom d'utilisateur
 */
void Settings::setUser(QString user)
{
    settings->beginGroup("SQL");
    settings->setValue("User", user);
    settings->endGroup();
}

/*!
 *  \brief Modification du mot de passe de l'utilisateur
 *
 *  Methode qui permet de modifier le mot de passe enregistre
 *  a utiliser avec l'utilisateur pour la connexion a la base de donnees
 *
 *  \param password : le mot de passe enregistrer
 */
void Settings::setPassword(QString password)
{
    settings->beginGroup("SQL");
    settings->setValue("Pass", password);
    settings->endGroup();
}

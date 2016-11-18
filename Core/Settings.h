#ifndef SETTINGS_H
#define SETTINGS_H

/*!
 * \file ./Core/Settings.h
 * \brief Gestion et sauvegarde des options
 * \author Florian Davin
 * \version 0.1
 */

#include <QSettings>
#include <QDebug>

/*! \class Settings
   * \brief Classe de gestions de l'ensemble des options
   *
   *  La classe permet de récupérer ou modifier l'ensemble des paramètres sauvegardés
   */
class Settings : public QSettings
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);
    //explicit Settings(QString organization = "Perso", QString application = "Softtech", QObject *parent = 0);
    ~Settings();

private:
    QString m_organization;
    QString m_application;
    QSettings *settings;
    
public slots:
    // Lecture des parametres
    QString getConnexion();
    QString getDbName();
    QString getHost();
    QString getUser();
    QString getPassword();
    int     getPort();
    
    // Ecriture des parametres
    void setDbName (QString dbName);
    void setHost (QString host);
    void setPort (int port);
    void setUser (QString user);
    void setPassword (QString password);
    void setConnexion (QString connexion);

    QString getApp() { return m_application; }
};

#endif // SETTINGS_H

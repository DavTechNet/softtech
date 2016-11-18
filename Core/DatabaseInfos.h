#ifndef DATABASEINFOS_H
#define DATABASEINFOS_H

#include <QObject>
#include <QSqlDatabase>
#include "Settings.h"

class DatabaseInfos : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseInfos(QObject *parent = 0);
    
private:
    
public slots:
    static QSqlDatabase SettingsInformations();
    static bool ParameterExist();
    
};

#endif // DATABASEINFOS_H

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include "../Core/Settings.h"
#include "../Core/Database.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    bool SaveParameters();
    
private:
    Ui::SettingsDialog *ui;

private slots:
    void ReadParameters();
    void SelectSQLiteDB();
    void CreateSQLiteDB();
    void CheckSqlConnect();
    void CreateSqlTable();

private slots:
    void DbChanged(QString type);

};

#endif // SETTINGSDIALOG_H

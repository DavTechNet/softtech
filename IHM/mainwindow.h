#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include <QItemSelection>
#include <QDate>
#include "../Core/Export.h"
#include "../Core/Database.h"
#include "../IHM/ExportDialog.h"
#include "../IHM/ImportDialog.h"
#include "../IHM/SettingsDialog.h"
#include "../IHM/AddDialog.h"
#include "../IHM/LoanDialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void connexionSlot();       // Creation des interfacages
    void SearchInDatabase(QString searchText);
    void slot_selectionChanged(const QItemSelection & selected, const QItemSelection & deselected);
    void SerialPresence(int index);
    void LoanInTime(bool state);
    void AddSoft();
    void SearchChanged(int index);
    void OpenSettings();
    void ExportDatabase();
    void ImportDatabase();
    void SaveDbChange();
    void CancelDbChange();
    void ChangeButtonsStatus(bool state);
    void ShowLoan();
    void DeleteSoft();

private:
    Ui::MainWindow *ui;
    void UpdateListSoft();
    void LoadDatabase();
    QSqlTableModel *tableSoft;
    QSqlTableModel *tableLoan;

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void editData();        // Signal correspondant a l'édition des données
};

#endif // MAINWINDOW_H

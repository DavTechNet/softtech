#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include "../Core/Import.h"

namespace Ui {
class ImportDialog;
}

class ImportDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ImportDialog(QWidget *parent = 0);
    ~ImportDialog();
    bool ImportData();
    QSqlTableModel *getTableSoft();
    QSqlTableModel *getTableLoan();

public slots:
    void FolderSoft();
    void FolderLoan();
    void FileTypeChanged(QString text);
    
private:
    Ui::ImportDialog *ui;
    QString filter;
    QSqlTableModel *soft;
    QSqlTableModel *loan;
};

#endif // IMPORTDIALOG_H

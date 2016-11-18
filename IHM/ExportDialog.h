#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include "../Core/Export.h"

namespace Ui {
class ExportDialog;
}

class ExportDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ExportDialog(QWidget *parent = 0);
    ~ExportDialog();
    QString getSeparator();
    QString getCodec();
    QString getSaveFolder();
    bool    getExportSoft();
    bool    getExportLoan();
    bool    exportData();

private:
    Ui::ExportDialog *ui;

private slots:
    void selectFolder();
};

#endif // EXPORTDIALOG_H

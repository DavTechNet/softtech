#include "ExportDialog.h"
#include "ui_ExportDialog.h"

ExportDialog::ExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportDialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_Folder, SIGNAL(clicked()),
            this, SLOT(selectFolder()));
}

ExportDialog::~ExportDialog()
{
    delete ui;
}

QString ExportDialog::getCodec()
{
    return ui->comboBox_codec->currentText();
}

QString ExportDialog::getSeparator()
{
    return ui->comboBox_separator->currentText();
}

QString ExportDialog::getSaveFolder()
{
    return ui->lineEdit_Folder->text();
}

bool ExportDialog::getExportSoft()
{
    return ui->checkBox_Soft->isChecked();
}

bool ExportDialog::getExportLoan()
{
    return ui->checkBox_Loan->isChecked();
}

void ExportDialog::selectFolder()
{
    QString folder =  QFileDialog::getExistingDirectory(this, tr("Sélection du répertoire d'exportation"),
                                                        QDir::homePath(), QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
    ui->lineEdit_Folder->setText(folder);
}

bool ExportDialog::exportData()
{
    Export exp;
    exp.setCodec(ui->comboBox_codec->currentText());
    exp.setSeparator(ui->comboBox_separator->currentText());
    exp.setDirectory(ui->lineEdit_Folder->text());
    QDir dir(ui->lineEdit_Folder->text());
    if (dir.exists() && ui->checkBox_Soft->isChecked() && ui->checkBox_Loan->isChecked())
    {
        exp.SoftToCsv(Database::ReadTableSoft());
        exp.LoanToCsv(Database::ReadTableLoan());
    }
    else if (dir.exists() && ui->checkBox_Soft->isChecked() && !ui->checkBox_Loan->isChecked())
        exp.SoftToCsv(Database::ReadTableSoft());
    else if (dir.exists() && !ui->checkBox_Soft->isChecked() && ui->checkBox_Loan->isChecked())
        exp.LoanToCsv(Database::ReadTableLoan());
    else if (!dir.exists())
    {
        QMessageBox::critical(0, tr("Erreur lors de l'exportation"), tr("Le répertoire n'existe pas."));
        return false;
    }
    return true;
}

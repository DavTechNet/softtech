#include "ImportDialog.h"
#include "ui_ImportDialog.h"

ImportDialog::ImportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportDialog)
{
    ui->setupUi(this);

    // Creation des actions sur les boutons
    connect(ui->pushButton_FileLoan, SIGNAL(clicked()),
            this, SLOT(FolderLoan()));
    connect(ui->pushButton_FileSoft, SIGNAL(clicked()),
            this, SLOT(FolderSoft()));

    filter = "Fichiers textes (*.csv)";
}

ImportDialog::~ImportDialog()
{
    delete ui;
}

void ImportDialog::FolderSoft()
{
    ui->lineEdit_FileSoft->setText(QFileDialog::getOpenFileName(0, tr("Sélectionnez le fichier contenant la liste des logiciels"),
                                                                QDir::homePath(), filter));
}

void ImportDialog::FolderLoan()
{
    ui->lineEdit_FileLoan->setText(QFileDialog::getOpenFileName(0, tr("Sélectionnez le fichier contenant la liste des emprunts"),
                                                                QDir::homePath(), filter));
}

void ImportDialog::FileTypeChanged(QString text)
{
    filter = "." + text;
}

bool ImportDialog::ImportData()
{
    Import import;
    import.setSeparator(ui->comboBox_Separator->currentText());
    import.setCodec(ui->comboBox_Codec->currentText());
    soft = new QSqlTableModel;
    loan = new QSqlTableModel;
    if (QFile::exists(ui->lineEdit_FileLoan->text()) && QFile::exists(ui->lineEdit_FileSoft->text()))
    {
        loan = import.ReadCsvLoan(ui->lineEdit_FileLoan->text());
        soft = import.ReadCsvSoft(ui->lineEdit_FileSoft->text());
    }
    else if (!QFile::exists(ui->lineEdit_FileLoan->text()) && QFile::exists(ui->lineEdit_FileSoft->text()))
        soft = import.ReadCsvSoft(ui->lineEdit_FileSoft->text());
    else if (QFile::exists(ui->lineEdit_FileLoan->text()) && !QFile::exists(ui->lineEdit_FileSoft->text()))
        loan = import.ReadCsvLoan(ui->lineEdit_FileLoan->text());
    else
    {
        QMessageBox::critical(0, tr("Erreur d'importation"), tr("Aucun fichier à importer!"));
        return false;
    }
    return true;
}

QSqlTableModel* ImportDialog::getTableLoan()
{
    return loan;
}

QSqlTableModel* ImportDialog::getTableSoft()
{
    return soft;
}

#include "Import.h"

Import::Import(QObject *parent) :
    QObject(parent)
{
}

void Import::setCodec(QString Codec)
{
    codec = Codec;
}

void Import::setSeparator(QString sep)
{
    separator = sep;
}

void Import::setFileSoft(QString file)
{
    fileSoft = file;
}

void Import::setFileLoan(QString file)
{
    fileLoan = file;
}

QString Import::getCodec()
{
    return codec;
}

QString Import::getSeparator()
{
    return separator;
}

QString Import::getFileLoan()
{
    return fileLoan;
}

QString Import::getFileSoft()
{
    return fileSoft;
}

QSqlTableModel* Import::ReadCsvSoft(QString filename)
{
    // Selection de la table a modifier
    QStringList listTable = QSqlDatabase::database().tables(QSql::Tables);
    listTable.removeAll("sqlite_sequence");
    QSqlTableModel *model = new QSqlTableModel(0, QSqlDatabase::database());
    model->setTable(listTable[0]);
    model->select();
    // Ajout des données
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!file.atEnd())
        {
            QString line = file.readLine();
            QStringList strings = line.split(separator);
            QSqlRecord record = model->record();
            record.setValue("title",            strings.value(0));
            record.setValue("editor",           strings.value(1));
            record.setValue("serial_y_n",       strings.value(2));
            record.setValue("serial",           strings.value(3));
            record.setValue("category",         strings.value(4));
            record.setValue("entry_date",       strings.value(5));
            record.setValue("out_date",         strings.value(6));
            record.setValue("out_destinataire", strings.value(7));
            record.setValue("prix",             strings.value(8));
            model->insertRecord(-1, record);
        }
        file.close();
    }
    return model;
}

QSqlTableModel* Import::ReadCsvLoan(QString filename)
{
    QStringList listTable = QSqlDatabase::database().tables(QSql::Tables);
    listTable.removeAll("sqlite_sequence");

    QSqlTableModel *model = new QSqlTableModel(0, QSqlDatabase::database());
    model->setTable(listTable[1]);
    model->select();
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!file.atEnd())
        {
            QString line = file.readLine();
            QStringList strings = line.split(separator);
            QSqlRecord record = model->record();
            record.setValue("emprunteur",   strings.value(1));
            record.setValue("date_emprunt", strings.value(2));
            record.setValue("date_retour",  strings.value(3));
            record.setValue("id_logiciel",  strings.value(4));
            model->insertRecord(-1, record);
        }
        file.close();
    }
    return model;
}

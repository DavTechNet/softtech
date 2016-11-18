#include "Export.h"

Export::Export(QObject *parent) :
    QObject(parent)
{
}

/*Export::Export(QObject *parent, QString separator, QString codec, QString directory) :
    QObject(parent)
{
    m_separator = separator;
    m_directory = directory;
    m_codec = codec;
}//*/

bool Export::ToCsv()
{
    // Lecture des données
    QList<QSqlQueryModel*> listModel = Database::ReadAllTables();

    // Conversion en Csv
    SoftToCsv(listModel.at(0));
    LoanToCsv(listModel.at(1));
    return true;
}

bool Export::SoftToCsv(QSqlQueryModel *tableSoft)
{
    // Recuperation des tables
    QStringList listTable = QSqlDatabase::database().tables(QSql::Tables);
    listTable.removeAll("sqlite_sequence");

    QString fileName = m_directory + "/table_" + listTable[0] + ".csv";
    //qDebug() << fileName;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux(&file);
    // On choisit le codec correspondant au jeu de caractère que l'on souhaite ; ici, UTF-8

    flux.setCodec(m_codec.toLocal8Bit());

    // On ecrit les données
    for (int row = 0; row < tableSoft->rowCount(); ++row)
    {
        QSqlRecord record = tableSoft->record(row);
        for (int field = 0; field < record.count(); ++field)
        {
            if (field > 0)
                flux << m_separator;
            flux << record.field(field).value().toString().replace("\n", "    ");
        }
        flux << "\n";
    }
    file.close();
    return true;
}

bool Export::LoanToCsv(QSqlQueryModel *tableLoan)
{
    // Recuperation des tables
    QStringList listTable = QSqlDatabase::database().tables(QSql::Tables);
    listTable.removeAll("sqlite_sequence");

    QString fileName = m_directory + "/table_" + listTable[1] + ".csv";
    //qDebug() << fileName;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux(&file);
    // On choisit le codec correspondant au jeu de caractère que l'on souhaite ; ici, UTF-8
    flux.setCodec(m_codec.toLocal8Bit());

    // On ecrit les données
    for (int row = 0; row < tableLoan->rowCount(); ++row)
    {
        QSqlRecord record = tableLoan->record(row);
        for (int field = 0; field < record.count(); ++field)
        {
            if (field > 0)
                flux << m_separator;
            flux << record.field(field).value().toString().replace("\n", "    ");
        }
        flux << "\n";
    }
    file.close();
    return true;
}

void Export::setCodec(QString codec)
{
    m_codec = codec;
}

void Export::setDirectory(QString directory)
{
    m_directory = directory;
}

void Export::setSeparator(QString separator)
{
    m_separator = separator;
}

#include "Database.h"

Database::Database(QObject *parent) :
    QObject(parent)
{
}

QList<QSqlQueryModel*> Database::ReadAllTables()
{
    QList<QSqlQueryModel*> listModel;

    // Recuperation de la liste des tables et suppression de la table par defaut
    QStringList listTable = QSqlDatabase::database().tables(QSql::Tables);
    listTable.removeAll("sqlite_sequence");

    listModel.append(ReadTableSoft());
    listModel.append(ReadTableLoan());
    return listModel;
}

QSqlQueryModel *Database::ReadTableSoft()
{
    QStringList listTable = QSqlDatabase::database().tables(QSql::Tables);
    listTable.removeAll("sqlite_sequence");

    QString query = "SELECT * FROM " + listTable[0];
    //qDebug() << query;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, "title");
    model->setHeaderData(1, Qt::Horizontal, "editor");
    model->setHeaderData(2, Qt::Horizontal, "serial_y_n");
    model->setHeaderData(3, Qt::Horizontal, "serial");
    model->setHeaderData(4, Qt::Horizontal, "category");
    model->setHeaderData(5, Qt::Horizontal, "entry_date");
    model->setHeaderData(6, Qt::Horizontal, "out_date");
    model->setHeaderData(7, Qt::Horizontal, "out_destinataire");
    model->setHeaderData(8, Qt::Horizontal, "prix");
    model->setHeaderData(9, Qt::Horizontal, "id");
    return model;
}

QSqlTableModel *Database::RWTableSoft()
{
    QStringList listTable = QSqlDatabase::database().tables(QSql::Tables);
    listTable.removeAll("sqlite_sequence");

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable(listTable[0]);
    model->select();
	model->setSort(0, Qt::AscendingOrder);
    model->setHeaderData(0, Qt::Horizontal, "title");
    model->setHeaderData(1, Qt::Horizontal, "editor");
    model->setHeaderData(2, Qt::Horizontal, "serial_y_n");
    model->setHeaderData(3, Qt::Horizontal, "serial");
    model->setHeaderData(4, Qt::Horizontal, "category");
    model->setHeaderData(5, Qt::Horizontal, "entry_date");
    model->setHeaderData(6, Qt::Horizontal, "out_date");
    model->setHeaderData(7, Qt::Horizontal, "out_destinataire");
    model->setHeaderData(8, Qt::Horizontal, "prix");
    model->setHeaderData(9, Qt::Horizontal, "id");
    return model;
}

QSqlQueryModel* Database::ReadTableLoan()
{
    QStringList listTable = QSqlDatabase::database().tables(QSql::Tables);
    listTable.removeAll("sqlite_sequence");

    QString query = "SELECT * FROM " + listTable[1] + " ORDER BY emprunteur";
    //qDebug() << query;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, tr("Emprunteur"));
    model->setHeaderData(2, Qt::Horizontal, tr("Date d'emprunt"));
    model->setHeaderData(3, Qt::Horizontal, tr("Date de retour"));
    model->setHeaderData(4, Qt::Horizontal, "id_logiciel");
    return model;
}

QSqlTableModel* Database::RWTableLoan()
{
    QStringList listTable = QSqlDatabase::database().tables(QSql::Tables);
    listTable.removeAll("sqlite_sequence");

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable(listTable[1]);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, "id");
    model->setHeaderData(1, Qt::Horizontal, "emprunteur");
    model->setHeaderData(2, Qt::Horizontal, "date_emprunt");
    model->setHeaderData(3, Qt::Horizontal, "date_retour");
    model->setHeaderData(4, Qt::Horizontal, "id_logiciel");
    return model;
}

QSqlQueryModel *Database::ReadTitleEditor()
{
    QStringList listTable = QSqlDatabase::database().tables(QSql::Tables);
    listTable.removeAll("sqlite_sequence");

    QString query = "SELECT title, editor, id FROM " + listTable[0];
    //qDebug() << query;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, tr("Titre"));
    model->setHeaderData(1, Qt::Horizontal, tr("Editeur"));
    return model;
}

QSqlQueryModel* Database::ReadBorrower()
{
    QStringList listTable = QSqlDatabase::database().tables(QSql::Tables);
    listTable.removeAll("sqlite_sequence");

    QString query = "SELECT emprunteur FROM " + listTable[1] + " ORDER BY emprunteur";
    //qDebug() << query;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, tr("Destinataire"));
    return model;
}

QSqlQueryModel* Database::SearchTableSoft(QString search, QString textSearch)
{
    QStringList listTable = QSqlDatabase::database().tables(QSql::Tables);
    listTable.removeAll("sqlite_sequence");

    QString query = "SELECT title, editor FROM " + listTable[0] +" WHERE " + search + " LIKE '%" + textSearch + "%'";
    //qDebug() << query;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, tr("Titre"));
    model->setHeaderData(1, Qt::Horizontal, tr("Editeur"));
    return model;
}

QSqlQueryModel* Database::SelectionSoft(QString title, QString editor)
{
    QStringList listTable = QSqlDatabase::database().tables(QSql::Tables);
    listTable.removeAll("sqlite_sequence");

    QString query = "SELECT * FROM " + listTable[0] + " WHERE title='" + title + "' AND editor='" + editor + "'";
    //qDebug() << query;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    return model;
}

bool Database::CreateSQLiteDB(QString fileName)
{
    // On ferme la base de données existante et on créer la nouvelle
    if (QSqlDatabase::database().isOpen())
    {
        QSqlDatabase::database().commit();
        QSqlDatabase::database().close();
        QSqlDatabase::database().removeDatabase(QSqlDatabase::database().connectionName());
    }

    QSqlDatabase base = QSqlDatabase::addDatabase("QSQLITE");
    base.setDatabaseName(fileName);

    if (!base.open())
    {
        QMessageBox::critical(0,tr("Erreur de création de la base de données"),base.lastError().text()) ;
        return false;
    }

    QStringList listeTables = base.tables() ;
    if (!listeTables.count() == 0 )
    {
        qDebug() << "Des tables existent déja, on sort..." ;
        return false;
    }

    QSqlQuery result ;
    result = base.exec("CREATE  TABLE logiciels (title VARCHAR, editor VARCHAR, serial_y_n VARCHAR, serial VARCHAR, category VARCHAR, entry_date DATE, out_date DATE, out_destinataire VARCHAR, prix FLOAT, id INTEGER PRIMARY KEY AUTOINCREMENT)");
    result = base.exec("CREATE TABLE emprunts   (id INTEGER PRIMARY KEY AUTOINCREMENT, emprunteur VARCHAR, date_emprunt DATE, date_retour DATE, id_logiciel INTEGER)");

    result = base.exec("CREATE  INDEX idx_logiciels ON logiciels (title ASC, editor ASC)");
    result = base.exec("CREATE  INDEX idx_emprunts  ON emprunts  (emprunteur ASC)");
    base.commit();
    base.close();
    return true;
}

QSqlQueryModel* Database::SoftInLoan(int idSoft)
{
    QStringList listTable = QSqlDatabase::database().tables(QSql::Tables);
    listTable.removeAll("sqlite_sequence");

    QString query = "SELECT * FROM " + listTable[1] + " WHERE id_logiciel='" + idSoft + "'";
    //qDebug() << query;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    return model;
}

QSortFilterProxyModel* Database::LoanInTime()
{
    QStringList listTable = QSqlDatabase::database().tables(QSql::Tables);
    listTable.removeAll("sqlite_sequence");

    QString query = "SELECT title, out_destinataire, out_date FROM " + listTable[0] + " ORDER BY title";
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, tr("Logiciel"));
    model->setHeaderData(1, Qt::Horizontal, tr("Emprunteur"));
    model->setHeaderData(2, Qt::Horizontal, tr("Date d'emprunt"));

    // On caches les logiciels non pretés
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(model);
    QRegExp rx("??/??/????");
    rx.setPatternSyntax(QRegExp::Wildcard);
    proxyModel->setFilterRegExp(rx);
    proxyModel->setFilterKeyColumn(2);
    return proxyModel;
}

QSqlRelationalTableModel* Database::HistoryLoan()
{
    QStringList listTable = QSqlDatabase::database().tables(QSql::Tables);
    listTable.removeAll("sqlite_sequence");

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel;
    model->setTable(listTable[1]);
    model->setRelation(4, QSqlRelation(listTable[0], "id", "title"));
    model->select();
    model->setHeaderData(0, Qt::Horizontal, "id");
    model->setHeaderData(1, Qt::Horizontal, tr("Emprunteur"));
    model->setHeaderData(2, Qt::Horizontal, tr("Date d'emprunt"));
    model->setHeaderData(3, Qt::Horizontal, tr("date de retour"));
    model->setHeaderData(4, Qt::Horizontal, tr("Logiciel"));
    return model;
}

#ifndef IMPORT_H
#define IMPORT_H

#include <QObject>
#include <QFile>
#include <QSqlRecord>
#include "Database.h"

class Import : public QObject
{
    Q_OBJECT
public:
    explicit Import(QObject *parent = 0);
    
signals:
    
private:
    QString fileSoft, fileLoan, separator, codec;

public slots:
    void setFileSoft(QString file);
    void setFileLoan(QString file);
    void setSeparator(QString sep);
    void setCodec (QString Codec);
    QString getCodec();
    QString getSeparator();
    QString getFileLoan();
    QString getFileSoft();
    QSqlTableModel *ReadCsvSoft(QString filename);
    QSqlTableModel *ReadCsvLoan(QString filename);
};

#endif // IMPORT_H

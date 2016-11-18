#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QPushButton>

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddDialog(QWidget *parent = 0);
    ~AddDialog();

public slots:
    QString getName();
    QString getEditor();
    QString getSerialList();
    QString getSerialReq();
    QString getCategory();
    QString getPrice();
    
private:
    Ui::AddDialog *ui;

private slots:
    void SerialRequired(QString text);
    void NamePresent(QString text);

};

#endif // ADDDIALOG_H

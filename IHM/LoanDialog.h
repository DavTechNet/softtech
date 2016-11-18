#ifndef LOANDIALOG_H
#define LOANDIALOG_H

#include <QDialog>
#include <QDesktopWidget>
#include "../Core/Database.h"

namespace Ui {
class LoanDialog;
}

class LoanDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoanDialog(QWidget *parent = 0);
    ~LoanDialog();
    void CenterOnScreen();

private slots:
    void LoanInTime();
    void LoanHistory();
    void SelectLoan(int index);
    
private:
    Ui::LoanDialog *ui;
};

#endif // LOANDIALOG_H

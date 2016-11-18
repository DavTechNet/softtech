#include "LoanDialog.h"
#include "ui_LoanDialog.h"

LoanDialog::LoanDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoanDialog)
{
    ui->setupUi(this);
    CenterOnScreen();
    SelectLoan(ui->comboBox_choiceLoan->currentIndex());

    // Bouton de fermeture de la fenetre
    connect(ui->pushButton_close, SIGNAL(clicked()),
            this, SLOT(close()));
    connect(ui->comboBox_choiceLoan, SIGNAL(currentIndexChanged(int)),
            this, SLOT(SelectLoan(int)));
}

LoanDialog::~LoanDialog()
{
    delete ui;
}

void LoanDialog::CenterOnScreen()
{
    QDesktopWidget screen;
    QRect screenGeom = screen.screenGeometry(this);

    int screenGeomX = screenGeom.center().x();
    int screenGeomY = screenGeom.center().y();

    move(screenGeomX - width() / 2,
         screenGeomY - height() / 2);
}

void LoanDialog::SelectLoan(int index)
{
    if (index == 0)
        LoanInTime();
    else if (index == 1)
        LoanHistory();
}

void LoanDialog::LoanHistory()
{
    ui->tableView_loan->setModel(Database::HistoryLoan());
    ui->tableView_loan->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
    ui->tableView_loan->verticalHeader()->setResizeMode(QHeaderView::Fixed);

    // On cache les colonnes inutiles
    //ui->tableView_loan->hideColumn(0);
}

void LoanDialog::LoanInTime()
{
    ui->tableView_loan->setModel(Database::LoanInTime());
    ui->tableView_loan->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
    ui->tableView_loan->verticalHeader()->setResizeMode(QHeaderView::Fixed);
    //ui->tableView_loan->showColumn(2);
}

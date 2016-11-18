#include "AddDialog.h"
#include "ui_AddDialog.h"

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);

    ui->lineEdit_price->setValidator(new QDoubleValidator(this));

    connect(ui->comboBox_serialReq, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(SerialRequired(QString)));
    connect(ui->lineEdit_name, SIGNAL(textChanged(QString)),
            this, SLOT(NamePresent(QString)));

    // Descativation du bouton de validation si nom vide
    QPushButton* pOkButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    if (ui->lineEdit_name->text().compare("") == 0)
        pOkButton->setEnabled(false);
    else
        pOkButton->setEnabled(true);
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::SerialRequired(QString text)
{
    if (text.compare(tr("Oui")) == 0)
        ui->textEdit_serialList->setEnabled(true);
    else
        ui->textEdit_serialList->setEnabled(false);
}

void AddDialog::NamePresent(QString text)
{
    QPushButton* pOkButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    if (text.compare("") == 0)
        pOkButton->setEnabled(false);
    else
        pOkButton->setEnabled(true);
}

QString AddDialog::getCategory()
{
    return ui->comboBox_category->currentText();
}

QString AddDialog::getName()
{
    return ui->lineEdit_name->text();
}

QString AddDialog::getEditor()
{
    return ui->lineEdit_editor->text();
}

QString AddDialog::getPrice()
{
    return ui->lineEdit_price->text();
}

QString AddDialog::getSerialList()
{
    return ui->textEdit_serialList->toPlainText();
}

QString AddDialog::getSerialReq()
{
    return ui->comboBox_serialReq->currentText();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), model(new QStandardItemModel(this))
{
    ui->setupUi(this);
    model->setHorizontalHeaderLabels({"Name", "Phone Number", "Email Address"});

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->resizeSection(0, 150);
    ui->tableView->horizontalHeader()->resizeSection(1, 300);
    ui->tableView->horizontalHeader()->resizeSection(2, 300);

    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_AddButton_clicked()
{
    QString name = ui->nameEdit->toPlainText();
    QString phoneNum = ui->phoneNumEdit->toPlainText();
    QString emailAddress = ui->emailEdit->toPlainText();

    Contact addContect(name,phoneNum,emailAddress);
    contactList.addContact(addContect);
    updateContactList();
    ui->nameEdit->clear();
    ui->phoneNumEdit->clear();
    ui->emailEdit->clear();

}

void MainWindow::on_RemoveButton_clicked()
{
    QString name = ui->nameEdit->toPlainText();
    contactList.removeContact(name);
    updateContactList();

    ui->nameEdit->clear();
    ui->phoneNumEdit->clear();
    ui->emailEdit->clear();
}

void MainWindow::on_saveContactListToFile_clicked()
{
    contactList.saveContactListToFile("../ContactListFile.txt");
}

void MainWindow::on_loadContactListFromFile_clicked()
{
    contactList.loadContactListFromFile("../ContactListFile.txt");
    updateContactList();
}

void MainWindow::updateContactList(){
    QList<QStandardItem*> row;
    model->clear();
    model->setHorizontalHeaderLabels({"Name", "Phone Number", "Email Address"});
    int rowIndex = 0;

    for (const Contact& contact : contactList.listContacts())
    {
        if (model->rowCount() <= rowIndex)
        {
            model->insertRow(rowIndex);
        }

        model->setItem(rowIndex, 0, new QStandardItem(contact.getName()));
        model->setItem(rowIndex, 1, new QStandardItem(contact.getPhoneNumber()));
        model->setItem(rowIndex, 2, new QStandardItem(contact.getEmailAddress()));

        ++rowIndex;
    }
}

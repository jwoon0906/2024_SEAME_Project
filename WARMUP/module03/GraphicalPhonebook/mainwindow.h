#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "ContactList.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateContactList();


private slots:
    void on_AddButton_clicked();

    void on_RemoveButton_clicked();

    void on_saveContactListToFile_clicked();

    void on_loadContactListFromFile_clicked();

private:
    Ui::MainWindow *ui;
    ContactList contactList;
    QStandardItemModel *model;

};
#endif // MAINWINDOW_H

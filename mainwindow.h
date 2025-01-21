#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <vector>
#include <string>
#include "recordmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addRecordButton_clicked();
    void on_showRecordsButton_clicked();
    void on_editRecordButton_clicked();
    void on_removeRecordButton_clicked();
    void on_sortRecordsButton_clicked();
    void on_searchRecordsButton_clicked();
    void on_saveToFileButton_clicked();
    void on_loadFromFileButton_clicked();


private:
    void showRecords();

    QTableWidget *recordsTable;
    QLineEdit *firstNameLineEdit, *middleNameLineEdit, *lastNameLineEdit;
    QLineEdit *dobLineEdit, *emailLineEdit, *phoneLineEdit;
    QPushButton *addRecordButton, *showRecordsButton, *editRecordButton;
    QPushButton *removeRecordButton, *sortRecordsButton, *searchRecordsButton;
    QPushButton *saveToFileButton, *loadFromFileButton;

    RecordManager *manager;
};
#endif // MAINWINDOW_H

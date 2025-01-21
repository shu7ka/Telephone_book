#include "mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <algorithm>
#include <QInputDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Устанавливаем центральный виджет
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    setWindowTitle("Record Management");
    resize(800, 600);

    // Создаем основной layout
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Создаем таблицу для отображения записей
    recordsTable = new QTableWidget(centralWidget);
    recordsTable->setColumnCount(6);
    recordsTable->setHorizontalHeaderLabels({"First Name", "Middle Name", "Last Name", "DOB", "Email", "Phone"});
    mainLayout->addWidget(recordsTable);

    // Создаем поля для ввода данных
    QFormLayout *formLayout = new QFormLayout();
    firstNameLineEdit = new QLineEdit(centralWidget);
    middleNameLineEdit = new QLineEdit(centralWidget);
    lastNameLineEdit = new QLineEdit(centralWidget);
    dobLineEdit = new QLineEdit(centralWidget);
    emailLineEdit = new QLineEdit(centralWidget);
    phoneLineEdit = new QLineEdit(centralWidget);

    formLayout->addRow("First Name:", firstNameLineEdit);
    formLayout->addRow("Middle Name:", middleNameLineEdit);
    formLayout->addRow("Last Name:", lastNameLineEdit);
    formLayout->addRow("Date of Birth:", dobLineEdit);
    formLayout->addRow("Email:", emailLineEdit);
    formLayout->addRow("Phone:", phoneLineEdit);

    mainLayout->addLayout(formLayout);

    // Кнопки для управления записями
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    addRecordButton = new QPushButton("Add Record", centralWidget);
    showRecordsButton = new QPushButton("Show All Records", centralWidget);
    editRecordButton = new QPushButton("Edit Record", centralWidget);
    removeRecordButton = new QPushButton("Remove Record", centralWidget);
    sortRecordsButton = new QPushButton("Sort Records", centralWidget);
    searchRecordsButton = new QPushButton("Search Records", centralWidget);
    saveToFileButton = new QPushButton("Save to File", centralWidget);
    loadFromFileButton = new QPushButton("Load from File", centralWidget);
    saveToDatabaseButton = new QPushButton("Save to Database", centralWidget);
    loadFromDatabaseButton = new QPushButton("Load from Database", centralWidget);

    buttonLayout->addWidget(addRecordButton);
    buttonLayout->addWidget(showRecordsButton);
    buttonLayout->addWidget(editRecordButton);
    buttonLayout->addWidget(removeRecordButton);
    buttonLayout->addWidget(sortRecordsButton);
    buttonLayout->addWidget(searchRecordsButton);
    buttonLayout->addWidget(saveToFileButton);
    buttonLayout->addWidget(loadFromFileButton);
    buttonLayout->addWidget(saveToDatabaseButton);
    buttonLayout->addWidget(loadFromDatabaseButton);


    mainLayout->addLayout(buttonLayout);

    // Подключаем кнопки к слотам
    connect(addRecordButton, &QPushButton::clicked, this, &MainWindow::on_addRecordButton_clicked);
    connect(showRecordsButton, &QPushButton::clicked, this, &MainWindow::on_showRecordsButton_clicked);
    connect(editRecordButton, &QPushButton::clicked, this, &MainWindow::on_editRecordButton_clicked);
    connect(removeRecordButton, &QPushButton::clicked, this, &MainWindow::on_removeRecordButton_clicked);
    connect(sortRecordsButton, &QPushButton::clicked, this, &MainWindow::on_sortRecordsButton_clicked);
    connect(searchRecordsButton, &QPushButton::clicked, this, &MainWindow::on_searchRecordsButton_clicked);
    connect(saveToFileButton, &QPushButton::clicked, this, &MainWindow::on_saveToFileButton_clicked);
    connect(loadFromFileButton, &QPushButton::clicked, this, &MainWindow::on_loadFromFileButton_clicked);
    connect(saveToDatabaseButton, &QPushButton::clicked, this, &MainWindow::on_saveToDatabaseButton_clicked);
    connect(loadFromDatabaseButton, &QPushButton::clicked, this, &MainWindow::on_loadFromDatabaseButton_clicked);



    // Инициализация менеджера записей
    manager = new RecordManager();
}

MainWindow::~MainWindow()
{
    delete manager;
}




// Слот для добавления записи
void MainWindow::on_addRecordButton_clicked()
{
   //Читаются значения из текстовых полей
    QString fName = firstNameLineEdit->text();
    QString mName = middleNameLineEdit->text();
    QString lName = lastNameLineEdit->text();
    QString dob = dobLineEdit->text();
    QString email = emailLineEdit->text();
    QString phone = phoneLineEdit->text();

    if (fName.isEmpty() || mName.isEmpty() || lName.isEmpty() || dob.isEmpty() || email.isEmpty() || phone.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all fields.");
        return;
    }
    // Проверка на правильность формата email
      QRegularExpression emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
      if (!emailRegex.match(email).hasMatch()) {
          QMessageBox::warning(this, "Input Error", "Please enter a valid email address.");
          return;
      }

      // Проверка на правильность формата телефона
      QRegularExpression phoneRegex("^\\+?\\d{10,15}$");
      if (!phoneRegex.match(phone).hasMatch()) {
          QMessageBox::warning(this, "Input Error", "Please enter a valid phone number.");
          return;
      }

      // Проверка на правильность формата даты
      QRegularExpression dobRegex("^\\d{2}\\-\\d{2}\\-\\d{4}$");
      if (!dobRegex.match(dob).hasMatch()) {
          QMessageBox::warning(this, "Input Error", "Please enter a valid date of birth (DD.MM.YYYY).");
          return;
      }

    PersonRecord record(fName.toStdString(), mName.toStdString(), lName.toStdString(),
                        dob.toStdString(), email.toStdString(), phone.toStdString());

    try {
        manager->Add(record);
        showRecords();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

// Слот для отображения всех записей
void MainWindow::on_showRecordsButton_clicked()
{
    showRecords();
}

//Обновление содержимого таблицы данными из менеджера записей.
void MainWindow::showRecords()
{
    recordsTable->setRowCount(0); //все строки удаляются

    std::vector<PersonRecord> records = manager->GetAllRecords(); //извлечение списка записей
    for (const auto &record : records) {
        int row = recordsTable->rowCount();
        recordsTable->insertRow(row);

        recordsTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(record.GetFirstName())));
        recordsTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(record.GetMiddleName())));
        recordsTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(record.GetLastName())));
        recordsTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(record.GetDateOfBirth())));
        recordsTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(record.GetEmail())));
        recordsTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(record.GetPhone())));
    }
}

// Слот для редактирования записи
void MainWindow::on_editRecordButton_clicked()
{
    int row = recordsTable->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "No Selection", "Please select a record to edit.");
        return;
    }

    PersonRecord record(
        recordsTable->item(row, 0)->text().toStdString(),
        recordsTable->item(row, 1)->text().toStdString(),
        recordsTable->item(row, 2)->text().toStdString(),
        recordsTable->item(row, 3)->text().toStdString(),
        recordsTable->item(row, 4)->text().toStdString(),
        recordsTable->item(row, 5)->text().toStdString()
    );

    // Перезаписываем данные в поля формы для редактирования
    firstNameLineEdit->setText(QString::fromStdString(record.GetFirstName()));
    middleNameLineEdit->setText(QString::fromStdString(record.GetMiddleName()));
    lastNameLineEdit->setText(QString::fromStdString(record.GetLastName()));
    dobLineEdit->setText(QString::fromStdString(record.GetDateOfBirth()));
    emailLineEdit->setText(QString::fromStdString(record.GetEmail()));
    phoneLineEdit->setText(QString::fromStdString(record.GetPhone()));

    // Обновляем запись
    manager->Edit(row, record);
    showRecords();
}

// Слот для удаления записи
void MainWindow::on_removeRecordButton_clicked()
{
    int row = recordsTable->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "No Selection", "Please select a record to remove.");
        return;
    }

    manager->Remove(row);
    showRecords();
}

// Слот для сортировки записей
void MainWindow::on_sortRecordsButton_clicked()
{
    // Предлагаем пользователю выбрать критерий сортировки
    QStringList sortOptions;
    sortOptions << "First Name" << "Middle Name" << "Last Name" << "Date of Birth" << "Email" << "Phone";

    bool ok;
    QString selectedOption = QInputDialog::getItem(this, "Sort Records", "Select field to sort by:", sortOptions, 0, false, &ok);

    if (ok && !selectedOption.isEmpty()) {
        // Теперь сортируем на основе выбранного поля
        if (selectedOption == "First Name") {
            manager->Sort([](const PersonRecord& a, const PersonRecord& b) {
                return a.GetFirstName() < b.GetFirstName();
            });
        } else if (selectedOption == "Middle Name") {
            manager->Sort([](const PersonRecord& a, const PersonRecord& b) {
                return a.GetMiddleName() < b.GetMiddleName();
            });
        } else if (selectedOption == "Last Name") {
            manager->Sort([](const PersonRecord& a, const PersonRecord& b) {
                return a.GetLastName() < b.GetLastName();
            });
        } else if (selectedOption == "Date of Birth") {
            manager->Sort([](const PersonRecord& a, const PersonRecord& b) {
                return a.GetDateOfBirth() < b.GetDateOfBirth();
            });
        } else if (selectedOption == "Email") {
            manager->Sort([](const PersonRecord& a, const PersonRecord& b) {
                return a.GetEmail() < b.GetEmail();
            });
        } else if (selectedOption == "Phone") {
            manager->Sort([](const PersonRecord& a, const PersonRecord& b) {
                return a.GetPhone() < b.GetPhone();
            });
        }

        // Обновляем отображение записей
        showRecords();
    }
}


// Слот для поиска записей
void MainWindow::on_searchRecordsButton_clicked()
{
    QString searchTerm = QInputDialog::getText(this, "Search", "Enter search term:");
    if (searchTerm.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Search term cannot be empty.");
        return;
    }

    std::vector<PersonRecord> results = manager->Search(searchTerm.toStdString());
    recordsTable->setRowCount(0);
    for (const auto &record : results) {
        int row = recordsTable->rowCount();
        recordsTable->insertRow(row);

        recordsTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(record.GetFirstName())));
        recordsTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(record.GetMiddleName())));
        recordsTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(record.GetLastName())));
        recordsTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(record.GetDateOfBirth())));
        recordsTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(record.GetEmail())));
        recordsTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(record.GetPhone())));
    }
}

// Слот для сохранения данных в файл
void MainWindow::on_saveToFileButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save to File", "", "Text Files (*.txt)");
    if (fileName.isEmpty()) {
        return;
    }

    try {
        manager->SaveToFile(fileName.toStdString());
        QMessageBox::information(this, "Success", "Data saved successfully.");
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

// Слот для загрузки данных из файла
void MainWindow::on_loadFromFileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.txt)");
    if (fileName.isEmpty()) {
        return;
    }

    try {
        manager->LoadFromFile(fileName.toStdString());
        showRecords();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::on_saveToDatabaseButton_clicked()
{
    if (!manager->ConnectToDatabase("records.db")) {
        QMessageBox::warning(this, "Database Error", "Unable to connect to database.");
        return;
    }

    manager->CreateTable(); // Создаем таблицу, если её нет
    manager->SaveToDatabase(); // Сохраняем в базу данных
    QMessageBox::information(this, "Success", "Data saved to database.");
}

void MainWindow::on_loadFromDatabaseButton_clicked()
{
    if (!manager->ConnectToDatabase("records.db")) {
        QMessageBox::warning(this, "Database Error", "Unable to connect to database.");
        return;
    }

    manager->LoadFromDatabase();
    showRecords();
    QMessageBox::information(this, "Success", "Data loaded from database.");
}



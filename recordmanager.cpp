#include "recordmanager.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlDatabase>
#include <iostream>
#include <QVariant>
#include<QtDebug>


RecordManager::RecordManager() {}

RecordManager::~RecordManager() {
    if (db.isOpen()) {
        db.close();
    }
}

// Подключение к базе данных
bool RecordManager::ConnectToDatabase(const std::string& dbName) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QString::fromStdString(dbName));

    if (!db.open()) {
        std::cerr << "Failed to open database: " << db.lastError().text().toStdString() << std::endl;
        return false;
    }
    return true;
}

// Создание таблицы, если она не существует
void RecordManager::CreateTable() {
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS records ("
               "firstName TEXT, "
               "middleName TEXT, "
               "lastName TEXT, "
               "dob TEXT, "
               "email TEXT, "
               "phone TEXT)");
}

// Сохранение данных в базу данных
void RecordManager::SaveToDatabase() {
    QSqlQuery query;
    query.prepare("INSERT INTO records (firstName, middleName, lastName, dob, email, phone) "
                  "VALUES (?, ?, ?, ?, ?, ?)");

    for (const auto& record : records) {
        query.addBindValue(QString::fromStdString(record.GetFirstName()));
        query.addBindValue(QString::fromStdString(record.GetMiddleName()));
        query.addBindValue(QString::fromStdString(record.GetLastName()));
        query.addBindValue(QString::fromStdString(record.GetDateOfBirth()));
        query.addBindValue(QString::fromStdString(record.GetEmail()));
        query.addBindValue(QString::fromStdString(record.GetPhone()));
        if (!query.exec()) {
            std::cerr << "Error inserting record: " << query.lastError().text().toStdString() << std::endl;
        }
    }
}

// Загрузка данных из базы данных
void RecordManager::LoadFromDatabase() {
    QSqlQuery query("SELECT * FROM records");
    records.clear();




    while (query.next()) {
        PersonRecord record(
            query.value(0).toString().toStdString(),
            query.value(1).toString().toStdString(),
            query.value(2).toString().toStdString(),
            query.value(3).toString().toStdString(),
            query.value(4).toString().toStdString(),
            query.value(5).toString().toStdString()
        );
        records.push_back(record);

    }

}

void RecordManager::Add(const PersonRecord& record)
{
    records.push_back(record);
}

void RecordManager::Remove(int index)
{
    if (index >= 0 && index < records.size()) {
        records.erase(records.begin() + index);
    }
}

void RecordManager::Edit(int index, const PersonRecord& updatedRecord)
{
    if (index >= 0 && index < records.size()) {
        records[index] = updatedRecord;
    }
}

void RecordManager::Sort(const std::function<bool(const PersonRecord&, const PersonRecord&)>& comparator)
{
    std::sort(records.begin(), records.end(), comparator);
}

std::vector<PersonRecord> RecordManager::GetAllRecords() const
{
    return records;
}

std::vector<PersonRecord> RecordManager::Search(const std::string& searchTerm) const
{
    std::vector<PersonRecord> results;
    for (const auto& record : records) {
        if (record.GetFirstName().find(searchTerm) != std::string::npos ||
            record.GetMiddleName().find(searchTerm) != std::string::npos ||
            record.GetLastName().find(searchTerm) != std::string::npos ||
            record.GetDateOfBirth().find(searchTerm) != std::string::npos ||
            record.GetEmail().find(searchTerm) != std::string::npos ||
            record.GetPhone().find(searchTerm) != std::string::npos) {
            results.push_back(record);
        }
    }
    return results;
}

void RecordManager::SaveToFile(const std::string& fileName) const
{
    std::ofstream file(fileName);
    for (const auto& record : records) {
        file << record.GetFirstName() << ","
             << record.GetMiddleName() << ","
             << record.GetLastName() << ","
             << record.GetDateOfBirth() << ","
             << record.GetEmail() << ","
             << record.GetPhone() << "\n";
    }
}

void RecordManager::LoadFromFile(const std::string& fileName)
{
    std::ifstream file(fileName);
    std::string line;
    records.clear();
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string firstName, middleName, lastName, dob, email, phone;

        std::getline(ss, firstName, ',');
        std::getline(ss, middleName, ',');
        std::getline(ss, lastName, ',');
        std::getline(ss, dob, ',');
        std::getline(ss, email, ',');
        std::getline(ss, phone, ',');

        records.push_back(PersonRecord(firstName, middleName, lastName, dob, email, phone));
    }
}

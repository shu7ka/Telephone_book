#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

#include <vector>
#include <string>
#include "personrecord.h"
#include <functional>  // Для std::function
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>



class RecordManager
{
public:
    RecordManager();
    ~RecordManager();

    void Add(const PersonRecord& record);
    void Remove(int index);
    void Edit(int index, const PersonRecord& updatedRecord);
    void Sort(const std::function<bool(const PersonRecord&, const PersonRecord&)>& comparator);
    std::vector<PersonRecord> GetAllRecords() const;
    std::vector<PersonRecord> Search(const std::string& searchTerm) const;
    void SaveToFile(const std::string& fileName) const;
    void LoadFromFile(const std::string& fileName);


    bool ConnectToDatabase(const std::string& dbName);
    void CreateTable();
    void SaveToDatabase();
    void LoadFromDatabase();

private:
    std::vector<PersonRecord> records;
     QSqlDatabase db;  // База данных SQLite
};

#endif // RECORDMANAGER_H

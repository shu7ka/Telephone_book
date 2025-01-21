#include "RecordManager.h"
#include "PersonRecord.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <sstream>

void RecordManager::SaveToFile(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file for writing.\n";
        return;
    }

    // Заголовок файла
    file << "First Name,Middle Name,Last Name,Date of Birth,Email,Phone\n";

    // Записываем все записи
    for (const auto& record : records) {
        file << record.GetFirstName() << ","
            << record.GetMiddleName() << ","
            << record.GetLastName() << ","
            << record.GetDateOfBirth() << ","
            << record.GetEmail() << ","
            << record.GetPhone() << "\n";
    }

    file.close();
    std::cout << "Data has been saved to " << filename << "\n";
}

void RecordManager::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file for reading.\n";
        return;
    }

    std::string line;
    std::getline(file, line);  // Пропускаем заголовок

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string fName, mName, lName, dob, mail, phone;

        std::getline(ss, fName, ',');
        std::getline(ss, mName, ',');
        std::getline(ss, lName, ',');
        std::getline(ss, dob, ',');
        std::getline(ss, mail, ',');
        std::getline(ss, phone, ',');

        PersonRecord record(fName, mName, lName, dob, mail, phone);
        records.push_back(record);
    }

    file.close();
    std::cout << "Data has been loaded from " << filename << "\n";
}

void RecordManager::Add(const PersonRecord& record) {
    records.push_back(record);
}

void RecordManager::Remove(size_t index) {
    if (index >= records.size()) throw std::out_of_range("Invalid record index.");
    records.erase(records.begin() + index);
}

void RecordManager::Edit(size_t index, const PersonRecord& updatedRecord) {
    if (index >= records.size()) throw std::out_of_range("Invalid record index.");
    records[index] = updatedRecord;
}

void RecordManager::DisplayAll() const {
    if (records.empty()) {
        std::cout << "No records available.\n";
        return;
    }
    for (const auto& record : records) {
        record.Display();
        std::cout << "--------------------\n";
    }
}

void RecordManager::SortByField(const std::string& field) {
    if (field == "firstName") {
        std::sort(records.begin(), records.end(), [](const PersonRecord& a, const PersonRecord& b) {
            return a.GetFirstName() < b.GetFirstName();
            });
    }
    else if (field == "lastName") {
        std::sort(records.begin(), records.end(), [](const PersonRecord& a, const PersonRecord& b) {
            return a.GetLastName() < b.GetLastName();
            });
    }
    else if (field == "dob") {
        std::sort(records.begin(), records.end(), [](const PersonRecord& a, const PersonRecord& b) {
            return a.GetDateOfBirth() < b.GetDateOfBirth();
            });
    }
    else {
        std::cout << "Invalid field for sorting.\n";
    }
}

std::vector<PersonRecord> RecordManager::Search(const std::string& query) const {
    std::vector<PersonRecord> result;

    for (const auto& record : records) {
        if (record.GetFirstName().find(query) != std::string::npos ||
            record.GetLastName().find(query) != std::string::npos ||
            record.GetDateOfBirth().find(query) != std::string::npos ||
            record.GetEmail().find(query) != std::string::npos ||
            record.GetPhone().find(query) != std::string::npos) {
            result.push_back(record);
        }
    }

    return result;
}

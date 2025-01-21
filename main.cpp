#include <iostream>
#include "RecordManager.h"
#include "Validators.h"

void AddRecord(RecordManager& manager);
void ShowAllRecords(const RecordManager& manager);
void EditRecord(RecordManager& manager);
void RemoveRecord(RecordManager& manager);
void SortRecords(RecordManager& manager);
void SearchRecords(const RecordManager& manager);
void SaveToFile(RecordManager& manager);
void LoadFromFile(RecordManager& manager);

int main() {
    RecordManager manager;

    int choice;
    do {
        std::cout << "Menu:\n"
            << "1. Add Record\n"
            << "2. Show Records\n"
            << "3. Edit Record\n"
            << "4. Remove Record\n"
            << "5. Sort Records\n"
            << "6. Search Records\n"
            << "7. Save to File\n"
            << "8. Load from File\n"
            << "0. Exit\nYour Choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            AddRecord(manager);
            break;
        case 2:
            ShowAllRecords(manager);
            break;
        case 3:
            EditRecord(manager);
            break;
        case 4:
            RemoveRecord(manager);
            break;
        case 5:
            SortRecords(manager);
            break;
        case 6:
            SearchRecords(manager);
            break;
        case 7:
            SaveToFile(manager);
            break;
        case 8:
            LoadFromFile(manager);
            break;
        case 0:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);

    return 0;
}

void AddRecord(RecordManager& manager) {
    std::string fName, mName, lName, dob, mail, phoneNum;
    std::cout << "Enter First Name: ";
    std::cin >> fName;
    std::cout << "Enter Middle Name: ";
    std::cin >> mName;
    std::cout << "Enter Last Name: ";
    std::cin >> lName;
    std::cout << "Enter Date of Birth (dd-mm-yyyy): ";
    std::cin >> dob;
    std::cout << "Enter Email: ";
    std::cin >> mail;
    std::cout << "Enter Phone Number: ";
    std::cin >> phoneNum;

    PersonRecord record(fName, mName, lName, dob, mail, phoneNum);
    manager.Add(record);
}

void ShowAllRecords(const RecordManager& manager) {
    manager.DisplayAll();
}

void EditRecord(RecordManager& manager) {
    size_t index;
    std::cout << "Enter record index to edit: ";
    std::cin >> index;

    std::string fName, mName, lName, dob, mail, phoneNum;
    std::cout << "Enter new First Name: ";
    std::cin >> fName;
    std::cout << "Enter new Middle Name: ";
    std::cin >> mName;
    std::cout << "Enter new Last Name: ";
    std::cin >> lName;
    std::cout << "Enter new Date of Birth (dd-mm-yyyy): ";
    std::cin >> dob;
    std::cout << "Enter new Email: ";
    std::cin >> mail;
    std::cout << "Enter new Phone Number: ";
    std::cin >> phoneNum;

    PersonRecord updatedRecord(fName, mName, lName, dob, mail, phoneNum);
    manager.Edit(index, updatedRecord);
}

void RemoveRecord(RecordManager& manager) {
    size_t index;
    std::cout << "Enter record index to remove: ";
    std::cin >> index;
    manager.Remove(index);
}

void SortRecords(RecordManager& manager) {
    std::string field;
    std::cout << "Enter field to sort by (firstName, lastName, dob): ";
    std::cin >> field;
    manager.SortByField(field);
}

void SearchRecords(const RecordManager& manager) {
    std::string query;
    std::cout << "Enter search query: ";
    std::cin >> query;
    std::vector<PersonRecord> results = manager.Search(query);

    std::cout << "Search Results:\n";
    for (const auto& record : results) {
        record.Display();
    }
}

void SaveToFile(RecordManager& manager) {
    std::string filename;
    std::cout << "Enter filename to save: ";
    std::cin >> filename;
    manager.SaveToFile(filename);
}

void LoadFromFile(RecordManager& manager) {
    std::string filename;
    std::cout << "Enter filename to load: ";
    std::cin >> filename;
    manager.LoadFromFile(filename);
}

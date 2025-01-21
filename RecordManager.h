#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

#include <vector>
#include <string>
#include "PersonRecord.h"

class RecordManager {
private:
    std::vector<PersonRecord> records;

public:
    void Add(const PersonRecord& record);
    void Remove(size_t index);
    void Edit(size_t index, const PersonRecord& updatedRecord);
    void DisplayAll() const;

    void SortByField(const std::string& field);  // ������� ����������
    std::vector<PersonRecord> Search(const std::string& query) const;  // ������� ������ �� ���������� �����

    void SaveToFile(const std::string& filename) const;  // ���������� � ����
    void LoadFromFile(const std::string& filename);  // �������� �� �����
};

#endif

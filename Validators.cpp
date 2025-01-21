#include "Validators.h"
#include <regex>
#include <string>
#include <algorithm>
#include <stdexcept>

namespace Validators {

    // �������� �������� � ������ � � ����� ������
    std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \t");
        size_t end = str.find_last_not_of(" \t");
        return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
    }

    // ��������� �������, ����� ��� �������� � ���������� �������� � ���������
    bool Name(const std::string& input) {
        // ������� ������� � �����
        std::string trimmedInput = trim(input);

        // ���������� ��������� ��� �������� �������, ����� ��� ��������
        static const std::regex namePattern(R"(^[A-Za-z�-��-���][A-Za-z�-��-���\s-]*[A-Za-z�-��-���]$)");

        // �������� � �������������� ����������� ���������
        return std::regex_match(trimmedInput, namePattern);
    }


    // ��������� ����
    bool Date(const std::string& input) {
        static const std::regex datePattern(R"(^\d{2}-\d{2}-\d{4}$)");
        if (!std::regex_match(input, datePattern)) return false;

        int day = std::stoi(input.substr(0, 2));
        int month = std::stoi(input.substr(3, 2));
        int year = std::stoi(input.substr(6, 4));

        const std::vector<int> daysInMonth = {
            31, 28 + (year % 4 == 0 ? 1 : 0), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
        };

        if (month < 1 || month > 12 || day < 1 || day > daysInMonth[month - 1]) return false;

        time_t now = time(nullptr);
        tm today = {};
        localtime_s(&today, &now);

        if (year > (today.tm_year + 1900) ||
            (year == (today.tm_year + 1900) && month > (today.tm_mon + 1)) ||
            (year == (today.tm_year + 1900) && month == (today.tm_mon + 1) && day > today.tm_mday)) {
            return false;
        }

        return true;
    }

    // ��������� email
    bool Email(const std::string& input) {
        static const std::regex emailPattern(R"(^[\w\.-]+@[\w\.-]+\.[a-zA-Z]{2,}$)");
        return std::regex_match(input, emailPattern);
    }

    // ��������� ����������� ������
    bool Phone(const std::string& input) {
        static const std::regex phonePattern(R"(^(\+?\d{1,2})?[\s\-]?(\(?\d{3}\)?)[\s\-]?\d{3}[\s\-]?\d{2}[\s\-]?\d{2}$)");
        return std::regex_match(input, phonePattern);
    }
}

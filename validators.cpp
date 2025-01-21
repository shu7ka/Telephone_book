#include "Validators.h"
#include <regex>
#include <string>
#include <algorithm>
#include <stdexcept>

namespace Validators {

    // Удаление пробелов в начале и в конце строки
    std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \t");
        size_t end = str.find_last_not_of(" \t");
        return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
    }

    // Валидация фамилии, имени или отчества с поддержкой латиницы и кириллицы
    bool Name(const std::string& input) {
        // Удаляем пробелы с краев
        std::string trimmedInput = trim(input);

        // Регулярное выражение для проверки фамилии, имени или отчества
        static const std::regex namePattern(R"(^[A-Za-zА-Яа-яЁё][A-Za-zА-Яа-яЁё\s-]*[A-Za-zА-Яа-яЁё]$)");

        // Проверка с использованием регулярного выражения
        return std::regex_match(trimmedInput, namePattern);
    }


    // Валидация даты
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

    // Валидация email
    bool Email(const std::string& input) {
        static const std::regex emailPattern(R"(^[\w\.-]+@[\w\.-]+\.[a-zA-Z]{2,}$)");
        return std::regex_match(input, emailPattern);
    }

    // Валидация телефонного номера
    bool Phone(const std::string& input) {
        static const std::regex phonePattern(R"(^(\+?\d{1,2})?[\s\-]?(\(?\d{3}\)?)[\s\-]?\d{3}[\s\-]?\d{2}[\s\-]?\d{2}$)");
        return std::regex_match(input, phonePattern);
    }
}

#include "PersonRecord.h"
#include "Validators.h"
#include <iostream>
#include <stdexcept>

PersonRecord::PersonRecord()
    : firstName("Unknown"), middleName("N/A"), lastName("Unknown"),
    dateOfBirth("01-01-1970"), email("default@domain.com"), phone("+0000000000") {}

PersonRecord::PersonRecord(const std::string& fName, const std::string& mName,
    const std::string& lName, const std::string& dob,
    const std::string& mail, const std::string& phoneNum)
    : firstName(fName), middleName(mName), lastName(lName),
    dateOfBirth(dob), email(mail), phone(phoneNum) {

    // Использование валидаторов
    if (!Validators::Name(fName)) {
        throw std::invalid_argument("Invalid first name format.");
    }
    if (!Validators::Name(mName)) {
        throw std::invalid_argument("Invalid middle name format.");
    }
    if (!Validators::Name(lName)) {
        throw std::invalid_argument("Invalid last name format.");
    }
    if (!Validators::Date(dob)) {
        throw std::invalid_argument("Invalid date format (expected dd-mm-yyyy).");
    }
    if (!Validators::Email(mail)) {
        throw std::invalid_argument("Invalid email format.");
    }
    if (!Validators::Phone(phoneNum)) {
        throw std::invalid_argument("Invalid phone number format.");
    }
}

void PersonRecord::Display() const {
    std::cout << "Name: " << firstName << " " << middleName << " " << lastName << "\n"
        << "DOB: " << dateOfBirth << "\n"
        << "Email: " << email << "\n"
        << "Phone: " << phone << "\n";
}

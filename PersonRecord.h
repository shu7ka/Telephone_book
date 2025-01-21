#ifndef PERSONRECORD_H
#define PERSONRECORD_H

#include <string>

class PersonRecord {
private:
    std::string firstName;
    std::string middleName;
    std::string lastName;
    std::string dateOfBirth;
    std::string email;
    std::string phone;

public:
    PersonRecord();
    PersonRecord(const std::string& fName, const std::string& mName,
        const std::string& lName, const std::string& dob,
        const std::string& mail, const std::string& phoneNum);

    void Display() const;

    // Геттеры
    std::string GetFirstName() const { return firstName; }
    std::string GetMiddleName() const { return middleName; }
    std::string GetLastName() const { return lastName; }
    std::string GetDateOfBirth() const { return dateOfBirth; }
    std::string GetEmail() const { return email; }
    std::string GetPhone() const { return phone; }

    // Сеттеры 
    void SetFirstName(const std::string& fName) { firstName = fName; }
    void SetMiddleName(const std::string& mName) { middleName = mName; }
    void SetLastName(const std::string& lName) { lastName = lName; }
    void SetDateOfBirth(const std::string& dob) { dateOfBirth = dob; }
    void SetEmail(const std::string& mail) { email = mail; }
    void SetPhone(const std::string& phoneNum) { phone = phoneNum; }
};

#endif

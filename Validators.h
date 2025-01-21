#ifndef VALIDATORS_H
#define VALIDATORS_H

#include <string>

namespace Validators {
    bool Name(const std::string& input);
    bool Date(const std::string& input);
    bool Email(const std::string& input);
    bool Phone(const std::string& input);
}

#endif // VALIDATORS_H

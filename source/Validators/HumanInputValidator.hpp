#pragma once

#include "IValidator.hpp"

class HumanInputValidator : public IValidator
{
    std::map<std::string, int>* number_to_position;

  public:
    HumanInputValidator(std::map<std::string, int>& number_to_position) : number_to_position(&number_to_position) {}

    bool operator() (std::string value) override
    {
        if (not std::all_of(value.begin(), value.end(), isdigit))
        {
            std::cerr << "incorrect input: number only" << std::endl;
            return false;
        }

        if (value.length() != 4)
        {
            std::cerr << "incorrect input: lenght of number shoud be 4" << std::endl;
            return false;
        }

        if (not number_to_position->contains(value))
        {
            std::cerr << "incorrect input: number should has unique digits" << std::endl;
            return false;
        }

        return true;
    }
};

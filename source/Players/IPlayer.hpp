#pragma once

#include "../Validator.hpp"
#include <string>
#include <vector>

using string = std::string;
template <class t> using matrix = std::vector<std::vector<t>>;

struct Response
{
    int cows;
    int bulls;
    string number;
};

struct IPlayer
{
    virtual string pickNumber(IValidator& validator) = 0;
    virtual string doGuess(IValidator& validator) = 0;
    virtual void getResponce(const Response& lastGuess) = 0;
};

#pragma once

#include "IPlayer.hpp"

class HumanPlayer : public IPlayer
{

  public:
    HumanPlayer() {}

    string pickNumber(IValidator& validator) override
    {
        string input;

        do
            std::cin >> input;
        while (not validator(input));

        return input;
    }

    string doGuess(IValidator& validator) override
    {
        string input;

        do
            std::cin >> input;
        while (not validator(input));

        return input;
    }

    void getResponce(const Response& lastGuess) override {}
};
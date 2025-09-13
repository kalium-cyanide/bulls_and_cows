#pragma once

#include "IPlayer.hpp"
#include <list>
#include <memory>

class ComputerPlayer : public IPlayer
{
    Response lastGuess;

    matrix<std::tuple<int, int>>* score_matrix;
    std::vector<std::string>* permutations;
    std::map<std::string, int>* number_to_position;
    std::list<std::string> possible_numbers;

  public:
    ComputerPlayer(matrix<std::tuple<int, int>>* score_matrix, std::vector<std::string>* permutations,
                   std::map<std::string, int>* number_to_position)
        : score_matrix(score_matrix), permutations(permutations), number_to_position(number_to_position),
          lastGuess({-1, -1, ""})
    {
        for (auto i : *permutations)
        {
            possible_numbers.push_back(i);
        }
    }

    string pickNumber(IValidator& validator) override {}

    string doGuess(IValidator& validator) override
    {
        auto [last_cows, last_bulls, last_number] = lastGuess;

        if (last_cows == -1 && last_bulls == -1)
        {
            return *possible_numbers.begin();
        }

        auto filtered = std::list<std::string>();
        auto last_pos = number_to_position->at(last_number);

        for (const auto& i : possible_numbers)
        {
            int current_pos = number_to_position->at(i);
            auto [cows, bulls] = (*score_matrix)[last_pos][current_pos];
            if (cows == last_cows and bulls == last_bulls)
            {
                filtered.push_back(i);
            }
        }

        possible_numbers = std::move(filtered);

        return *possible_numbers.begin();
    }

    void getResponce(const Response& lastGuess) override { this->lastGuess = lastGuess; }
};

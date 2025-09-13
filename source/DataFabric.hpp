#pragma once

#include <fstream>
#include <map>
#include <stdexcept>
#include <tuple>
#include <vector>

template <class t> using matrix = std::vector<std::vector<t>>;

class DataFabric
{
  public:
    static matrix<std::tuple<int, int>>* create_score_matrix()
    {
        auto result = new std::vector(5040, std::vector(5040, std::tuple<int, int>()));
        auto score_matrix_file = std::ifstream("score_matrix.bin", std::ios::binary);

        if (not score_matrix_file)
        {
            throw std::runtime_error("can't open score_matrix.bin");
        }

        for (int i = 0; i < 5040; i++)
            for (int j = 0; j < 5040; j++)
            {
                auto score = char();
                score_matrix_file.read(&score, 1);

                (*result)[i][j] = std::tuple((score >> 4) & 0x0F, score & 0x0F);
            }

        return result;
    }

    static std::map<std::string, int>* create_number_to_position(const std::vector<std::string>& permutations)
    {
        auto result = new std::map<std::string, int>();

        for (int i = 0; i < 5040; i++)
        {
            result->insert({permutations[i], i});
        }

        return result;
    }

    static std::vector<std::string>* create_permutations()
    {
        auto result = new std::vector<std::string>();
        auto permutations_file = std::ifstream("permutations.bin", std::ios::binary);

        if (not permutations_file)
        {
            throw std::runtime_error("can't open permutations.bin");
        }

        for (int i = 0; i < 5040; i++)
        {
            char buffer[5] = {0, 0, 0, 0, 0};
            permutations_file.read(buffer, 4);

            result->push_back(std::string(buffer));
        }

        return result;
    }
};
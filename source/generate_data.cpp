#include <algorithm>
#include <array>
#include <cctype>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <ranges>
#include <set>
#include <string>
#include <tuple>
#include <vector>

template <class t> using matrix = std::vector<std::vector<t>>;
using permutation_container = std::vector<std::string>;

char get_cows_and_bulls(std::string hidden_number, std::string guessed_number)
{
    auto cows = int();
    auto bulls = int();

    for (int i = 0; i < 4; i++)
    {
        if (hidden_number[i] == guessed_number[i])
        {
            bulls++;
            hidden_number[i] = '_';
        }
        for (int j = 0; j < 4; j++)
        {
            if (hidden_number[i] == guessed_number[j])
            {
                cows++;
                hidden_number[i] = 'H';
                guessed_number[j] = 'G';
            }
        }
    }

    return (cows << 4) + bulls;
}

permutation_container get_permutations()
{
    permutation_container result;
    std::string digits = "0123456789";

    do
    {
        result.push_back(std::string(digits.begin(), digits.begin() + 4));
        std::reverse(digits.begin() + 4, digits.begin() + 10);
    }
    while (std::next_permutation(digits.begin(), digits.begin() + 10));

    return result;
}

matrix<char> get_score_matrix(permutation_container& permutations)
{
    auto dp = std::vector(5040, std::vector(5040, char()));

    for (auto i = 0; i < 5040; i++)
    {
        for (auto j = 0; j < 5040; j++)
        {
            dp[i][j] = get_cows_and_bulls(permutations[i], permutations[j]);
        }
    }

    return dp;
}

int main()
{
    auto start = std::chrono::steady_clock::now();

    auto permutations = get_permutations();
    auto score_matrix = get_score_matrix(permutations);

    auto permutation_file = std::ofstream("permutations.bin", std::ios::binary);
    auto score_matrix_file = std::ofstream("score_matrix.bin", std::ios::binary);

    for (const auto& i : permutations)
    {
        permutation_file.write(i.c_str(), 4);
    }

    for (auto i = 0; i < 5040; i++)
        for (auto j = 0; j < 5040; j++)
        {
            score_matrix_file.write(&score_matrix[i][j], 1);
        }

    permutation_file.close();
    score_matrix_file.close();

    auto end = std::chrono::steady_clock::now();

    std::cout << "done in " << double((end - start).count()) / 1'000'000'000 << "s\n";

    return 0;
}
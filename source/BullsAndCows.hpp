#include "DataFabric.hpp"
#include "Players.hpp"
#include "Players/ComputerPlayer.hpp"
#include "Players/HumanPlayer.hpp"
#include "Players/IPlayer.hpp"
#include "Validator.hpp"
#include <iterator>
#include <memory>
#include <random>
#include <tuple>

#define ptr(x) std::make_unique<decltype(x)>(x)

class BullsAndCows
{
    std::unique_ptr<IPlayer> player1;
    std::unique_ptr<IPlayer> player2;

    std::unique_ptr<IValidator> validator1;
    std::unique_ptr<IValidator> validator2;

    std::unique_ptr<matrix<std::tuple<int, int>>> score_matrix;
    std::unique_ptr<std::map<std::string, int>> number_to_position;
    std::unique_ptr<std::vector<std::string>> permutations;

    std::string gameNumber;

    std::string get_game_number()
    {
        static std::string digits = "0123456789";

        static std::random_device rd;
        static std::mt19937 mt{rd()};

        std::shuffle(digits.begin(), digits.end(), mt);

        return std::string(digits.begin(), digits.begin() + 4);
    }

    void start()
    {
        gameNumber = get_game_number();

        step(1);
    }

    void step(int round)
    {
        auto p1Guess = player1->doGuess(*validator1);
        auto p2Guess = player2->doGuess(*validator2);

        auto [p1Cows, p1Bulls] = (*score_matrix)[(*number_to_position)[gameNumber]][(*number_to_position)[p1Guess]];
        auto [p2Cows, p2Bulls] = (*score_matrix)[(*number_to_position)[gameNumber]][(*number_to_position)[p2Guess]];

        player1->getResponce({p1Cows, p1Bulls, p1Guess});
        player2->getResponce({p2Cows, p2Bulls, p2Guess});

        std::cout << std::endl << "r: " << round << ":\t" << p1Guess << '\t' << p2Guess << std::endl;
        std::cout << "\tb" << p1Bulls << " c" << p1Cows << '\t' << "b" << p2Bulls << " c" << p2Cows << std::endl;

        if (p1Bulls == 4 and p2Bulls == 4)
        {
            end(0, round);
            return;
        }
        if (p1Bulls == 4)
        {
            end(-1, round);
            return;
        }
        if (p2Bulls == 4)
        {
            end(1, round);
            return;
        }

        step(round + 1);
    }

    void end(int winner, int round)
    {
        if (winner == -1)
            std::cout << "\nPlayer1 WIN in " << round << "!\n";
        if (winner == 0)
            std::cout << "\nDraw in " << round << "!\n";
        if (winner == 1)
            std::cout << "\nPlayer2 WIN in " << round << "!\n";

        std::cout << "\n";
    }

  public:
    BullsAndCows()
    {
        score_matrix.reset(DataFabric::create_score_matrix());
        permutations.reset(DataFabric::create_permutations());
        number_to_position.reset(DataFabric::create_number_to_position(*permutations));
    }

    void startHumanVsComputer()
    {
        auto p1 = new HumanPlayer();
        auto p2 = new ComputerPlayer(score_matrix.get(), permutations.get(), number_to_position.get());

        auto v1 = new HumanInputValidator(*number_to_position);
        auto v2 = new ComputerInputValidator(*number_to_position);

        player1.reset(p1);
        player2.reset(p2);

        validator1.reset(v1);
        validator2.reset(v2);

        start();
    }

    void startHumanVsHuman()
    {
        auto p1 = new HumanPlayer();
        auto p2 = new HumanPlayer();

        auto v1 = new HumanInputValidator(*number_to_position);
        auto v2 = new HumanInputValidator(*number_to_position);

        player1.reset(p1);
        player2.reset(p2);

        validator1.reset(v1);
        validator2.reset(v2);

        start();
    }
};
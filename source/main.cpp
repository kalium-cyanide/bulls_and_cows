#include "BullsAndCows.hpp"
#include "Players/HumanPlayer.hpp"
#include "Players/IPlayer.hpp"
#include <exception>

void gameLoop()
{
    auto game = BullsAndCows();

    while (true)
    {
        std::cout << "Write number:\n";
        std::cout << "  1. Play vs Human\n";
        std::cout << "  2. Play vs Computer\n";
        std::cout << "  q. Quit\n";

        auto command = std::string();
        std::cin >> command;

        system("cls");
        if (command == "q")
        {
            return;
        }
        if (command == "1")
        {
            game.startHumanVsHuman();
            std::cin.get();
        }
        if (command == "2")
        {
            game.startHumanVsComputer();
            std::cin.get();
        }
    }
}

int main()
{
    try
    {
        gameLoop();
    }
    catch (std::exception error)
    {
        std::cerr << error.what();
        return -1;
    }

    return 0;
}
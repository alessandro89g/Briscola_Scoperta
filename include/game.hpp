#ifndef GAME_H
#define GAME_H

#include <vector>
#include <sstream>
#include <string>
#include "player.hpp"
#include "table.hpp"

#define NCARDS 40

class Game
{
    std::stringstream _header;
    int _nPlayers;
    std::vector<Player> _players;
    Table _table;
    Card _briscola;
    int _lastToEat = 0;


    void clearAndPrepare();
    void prepareDeck();
    void everybodyPickCard();
    void printTable();
    void printScreen();
    int winningPlayer();
    bool isBriscola(const Card& card);


public:
    Game();
    Game(std::vector<std::string> names);
    void run();
};

#endif // GAME_H

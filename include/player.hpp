#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>
#include "card.hpp"

static int s_player_number = 0;

class Player
{
    std::vector<Card> _hand;
    std::vector<Card> _cardsEaten;
    std::string _playerName;
    int _playerID;

public:
    Player();
    Player(std::string name);
    const std::string name() const;
    void clear();
    void pickCard(Card card);
    Card putCard(int n);
    std::string cards() const;
    int getId() const {return _playerID; }
    void getsCards(const std::vector<Card>& cardsOnTable) {
        _cardsEaten.insert(_cardsEaten.end(),cardsOnTable.begin(),cardsOnTable.end());
    }
    int getPoints() const {
        int points = 0;
        for (const Card& card: _cardsEaten)
            points += card.points();
        return points;
    }
};

#endif // PLAYER_H

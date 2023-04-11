#ifndef TABLE_H
#define TABLE_H
#include "card.hpp"
#include "player.hpp"

class Table
{
    std::vector<Card> _cards;   //Cards being thrown in a round
    std::vector<Card> _deck;    //Remaining cards

public:
    Table() = default;
    Table(const std::vector<Card>& deck);
    void print();
    void setDeck(const std::vector<Card>& deck);
    Card pickCard();
    std::vector<Card> cardsOnTable() const;
    int cardsLeft() const;
    Card nextCard() const;
    void throwCard(const Card& card);
    void clear();
    void removeCardsThrown() {
        _cards.clear();
    }
};

#endif // TABLE_H

#include "table.hpp"

Table::Table(const std::vector<Card> &deck)
    : _deck(deck)
{

}

void Table::setDeck(const std::vector<Card> &deck) {
    _deck = deck;
}

Card Table::pickCard() {
    Card card = _deck.back();
    _deck.pop_back();
    return card;
}

std::vector<Card> Table::cardsOnTable() const  {
    return _cards;
}

int Table::cardsLeft() const {
    return _deck.size();
}

Card Table::nextCard() const {
    return _deck.back();
}

void Table::throwCard(const Card &card) {
    int i=0;
    _cards.push_back(card);
}

void Table::clear() {
    _deck.clear();
    _cards.clear();
}

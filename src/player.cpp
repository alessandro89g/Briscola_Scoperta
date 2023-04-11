#include "player.hpp"
#include <algorithm>

Player::Player()
    : _playerID(s_player_number++)
{
    _playerName= "Player_";
    _playerName.append(std::to_string(s_player_number));
}

Player::Player(std::string name)
    : _playerID(s_player_number++), _playerName(name)
{

}

const std::string Player::name() const {
    return _playerName;
}

void Player::clear() {
    _hand.clear();
    _cardsEaten.clear();
}

void Player::pickCard(Card card) {
    if (_hand.size()>2) {
        std::cerr << "The hand is full!\n";
        exit(1);
    }
    card.setOwner(_playerID);
    _hand.push_back(card);
}

Card Player::putCard(int n)
{
    Card card = _hand[n];
    _hand.erase(_hand.begin()+n);
    return card;
}

std::string Player::cards() const
{
    std::string cardString = "";
    for (const Card& card : _hand)
        cardString += card.toString();
    return cardString;
}

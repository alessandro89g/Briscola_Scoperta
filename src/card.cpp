#include "card.hpp"

Card::Card(Type type, Suit suit)
    : _type(type), _suit(suit)
{

}

std::string Card::toString() const {
    std::string card = "[";
    switch (_type) {
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
        card += std::to_string(_type);
        break;
    case 8:
        card += "J";
        break;
    case 9:
        card += "Q";
        break;
    case 10:
        card += "K";
        break;
    case 11:
        card += "3";
        break;
    case 12:
        card += "A";
        break;

    }


    switch (_suit) {
    case Hearts:
        card += u8"\u2665";
        break;
    case Clubs:
        card += u8"\u2663";
        break;
    case Diamonds:
        card += u8"\u2666";
        break;
    case Spades:
        card += u8"\u2660";
        break;
    }
    card += ']';
    return card;
}

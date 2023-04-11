#ifndef CARD_H
#define CARD_H

#include <string>

#define NSUIT 4
#define TYPEMAX 12

class Card
{
public:
    enum Suit {Hearts, Clubs, Diamonds, Spades};
    enum Type {Two = 2, Four = 4, Five, Six, Seven, Jack, Queen, King, Three = 11, Ace = 12};

private:
    Suit _suit;
    Type _type;
    int _ownerID = -1;

public:
    Card() = default;
    Card(Type type, Suit suit);
    Card (const Card &other) {
        _suit = other._suit;
        _type = other._type;
        _ownerID = other._ownerID;
    }
    Suit getSuit() const {return _suit; }
    void setSuit(Suit suit) {_suit = suit; }
    Type getType() const {return _type; }
    void setType(Type type) {_type = type; }
    int getOwner() const {return _ownerID;}
    void setOwner(int ownerID) {_ownerID = ownerID; }

    std::string toString() const;

    bool operator > (const Card& other) {
        if (_suit!=other._suit) //A card that comes after another, if of different suit loses (unless
            return true;        // it is briscola, but we don't know that here
        return _type > other._type;
    }
    bool operator < (const Card& other) {
        return !(*this>other);
    }

    Card& operator = (const Card& other) {
        if (this != &other){
            _suit = other._suit;
            _type = other._type;
            _ownerID = other._ownerID;
        }
        return *this;
    }
    int points() const {
        switch (_type) {
            case Jack:
                return 2;
            case Queen:
                return 3;
            case King:
                return 4;
            case Three:
                return 10;
            case Ace:
                return 11;
            default:
                return 0;
        }
    }
};

#endif // CARD_H

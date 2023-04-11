#include "game.hpp"
#include "utils.hpp"
#include <iostream>
#include <algorithm>
#include <random>

Game::Game()
    :_nPlayers(2)
{
    printCut();
    _header << "Welcome to Briscola!\n\n";
    _header << "Numbers of players: " << _nPlayers << '\n';

    for(int i=0; i<_nPlayers; i++) {
        _players.emplace_back(Player());
        _header << "Player "<<i<< " : " << _players[i].name() << '\n';
    }
    std::cout << _header.str();
}

Game::Game(std::vector<std::string> names)
{
    printCut();
    _header << "Welcome to Briscola!\n\n";
    _nPlayers = names.size();
    _header  << "Numbers of players: " << _nPlayers << '\n';

    for(int i=0; i<_nPlayers; i++) {
        _players.emplace_back(Player(names[i]));
        _header << "Player "<<i<< " : "<< _players[i].name() << '\n';
    }
    std::cout << _header.str();
}

void Game::run()
{
    clearAndPrepare();
    while (_table.cardsLeft()) {
        printScreen();

        for (int i=0; i<_nPlayers; i++) {
            int j = (i+_lastToEat)%_nPlayers;
            std::cout << _players[j].name() << " put a card (1,2,3): ";
            int n;
            std::cin >> n;
            _table.throwCard(_players[j].putCard(n));
            printScreen();
        }
        printScreen();
        _lastToEat = winningPlayer();
        _players[_lastToEat].getsCards(_table.cardsOnTable());
        _table.removeCardsThrown();
        everybodyPickCard();
    }

    for (int i=0; i<3; i++) {
        printScreen();

        for (int i=0; i<_nPlayers; i++) {
            int j = (i+_lastToEat)%_nPlayers;
            std::cout << _players[j].name() << " put a card (1,2,3): ";
            int n;
            std::cin >> n;
            _table.throwCard(_players[j].putCard(n-1));
            printScreen();
        }
        printScreen();
        _lastToEat = winningPlayer();
        _players[_lastToEat].getsCards(_table.cardsOnTable());
        _table.removeCardsThrown();
    }




    Player winner = _players[0];
    for(const auto& player: _players){
        std::cout << "Player " << player.name() << " has: " << player.getPoints() << '\n';
        if (player.getPoints()>winner.getPoints())
            winner = player;
    }
    std::cout << winner.name() << " is the winner with " << winner.getPoints() << " points\n";

}

void Game::clearAndPrepare()
{
    clearScreen();
    _table.clear();

    for(Player& p : _players)
        p.clear();

    prepareDeck();

    for (int i=0; i<3; i++)
        everybodyPickCard();
}

void Game::prepareDeck()
{
    std::vector<Card> deck;
    deck.reserve(NCARDS);
    for (int i=0; i<NSUIT; i++) {               //Fills the deck
        for (int j=2; j<=TYPEMAX; j++){
            if (j==3)
                continue;
            deck.emplace_back(Card::Type(j),Card::Suit(i));
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(deck.begin(),deck.end(),gen);   //Shuffles it


    _briscola = deck[0];                            //"First" card is set at briscola and set at the end
    _header << "\nBriscola: " << _briscola.toString().substr(2,3) << '\n';
    _table.setDeck(deck);   //Put the deck on the table leaving to it the ownership
}

void Game::everybodyPickCard()
{
    for(Player& player : _players)
        player.pickCard(_table.pickCard());
}

void Game::printTable()
{
    //Prints first player
    std::cout << "\t"+ _players[0].name()+"'s hand:    " + _players[0].cards() << "\n\n";

    //Prints the table
        if (_table.cardsLeft())
            std::cout << "\t\tDeck: "+_briscola.toString()<< "   ("
                      << _table.cardsLeft()-1  << _table.nextCard().toString()<<")";
        if (_table.cardsOnTable().size())
            std::cout << "\n\n\t\t -> cards thrown:\n";
        for (const Card& card: _table.cardsOnTable()){
            std::cout << "\t\t\t" << _players[card.getOwner()].name() << card.toString() << "\n";
        }
        std::cout << "\n\n";
    //End printing table

    //Prints second player
    std::cout << "\t"+ _players[1].name()+"'s hand:   " + _players[1].cards() << '\n';
}

void Game::printScreen() {
    clearScreen();
    printCut();
    std::cout << _header.str();
    printCut();
    printTable();
    printCut();
}

int Game::winningPlayer()
{
    std::vector<Card> hand = _table.cardsOnTable();
    Card winning = hand[0];
    for(int i=1; i<_nPlayers; i++) {
        if (isBriscola(winning) && isBriscola(hand[i])) {   //If both are briscolas the one
            if (hand[i]>winning)                            //with the biggest value wins
                winning = hand[i];
        }
        else if (isBriscola(winning) && !isBriscola(hand[i]))//If the current winning is not briscola
            continue;                                        //but the other is, it wins
        else if (!isBriscola(winning) && isBriscola(hand[i]))//If the current winning is briscola and the
            winning = hand[i];                               //second is not the first wins
        else {
            if (winning < hand[i])                          //If neither are briscolas the
                winning = hand[i];                          //Suit that started the hand and has
                                                            //the highest values wins (hidden in <)
        }
    }
    std::cout << "This hand is won by: " << _players[winning.getOwner()].name() << '\n';
    std::cout << "Press any key to continue to next round";
    std::cin.get();
    std::cin.get();
    return winning.getOwner();  //Returns the index of the owner of the winning card
}

bool Game::isBriscola(const Card &card)
{
    if (card.getSuit()==_briscola.getSuit())
        return true;
    return false;
}

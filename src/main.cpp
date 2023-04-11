#include <iostream>
#include "game.hpp"

using namespace std;

int main()
{
    Game g({"Alessandro", "Giacomo"});
    g.run();

    cin.get();
    cin.get();
    return 0;
}

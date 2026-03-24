/// Project entry point
#include <iostream>
#include "game.h"
#include "../test/test.h"

int main(int argc, const char* argv[])
{
    if (!test())
    {
        std::cout << "Tests NO superados. Los has definido ya?" << std::endl;
    }
    else
    {
        std::cout << "Test superados." << std::endl;
    }

    if (!testShould())
    {
        std::cout << "TestShould NO superado" << std::endl;
    }
    else
    {
        std::cout << "TestShould superado." << std::endl;
    }
    if (!testBoard())
    {
        std::cout << "TestBoard NO superado" << std::endl;
    }
    else
    {
        std::cout << "TestBoard superado." << std::endl;
    }
    if (!testGettersSetters())
    {
        std::cout << "TestGettersSetters NO superado" << std::endl;
    }
    else
    {
        std::cout << "TestGetterssSetters superado." << std::endl;
    }
    if (!testExplodeAndDrop())
    {
        std::cout << "TestExplodeAndDrop NO superado" << std::endl;
    }
    else
    {
        std::cout << "TestExplodeAndDrop superado." << std::endl;
    }
    


    // The following code runs the graphic part
    Game game;
    // Run until ESC is pressed
    game.run();
    return 0;
}

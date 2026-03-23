#include <filesystem>
#include "board.h"
#include "candy.h"
#include "controller.h"
#include "game.h"
#include "util.h"
#include <iostream>

void imprimirTablero(const Board& b) 
{
    std::cout << "\n=== TABLERO 10x10 ===\n";
    
    
    for (int y = 0; y < b.getHeight(); y++) 
    {
        for (int x = 0; x < b.getWidth(); x++) 
        {
            Candy* c = b.getCell(x, y);
            
            if (c == nullptr) 
            {
                std::cout << ". ";
            }
           else 
            {
                if (c->getType() == CandyType::TYPE_RED)
                    std::cout << "R ";
                else if (c->getType() == CandyType::TYPE_BLUE)
                    std::cout << "B ";
                else if (c->getType() == CandyType::TYPE_GREEN)
                    std::cout << "G ";
                else if (c->getType() == CandyType::TYPE_YELLOW)
                    std::cout << "Y ";
                else if (c->getType() == CandyType::TYPE_PURPLE)
                    std::cout << "P ";
                else if (c->getType() == CandyType::TYPE_ORANGE)
                    std::cout << "O ";
                else
                    std::cout << "? ";
            }
        }
        std::cout << "\n"; 
    }
    std::cout << "\n\n\n";
}

void imprimirTableroBool(const Board& b) 
{
    std::cout << "\n=== TABLERO 10x10 ===\n";
    
    
    for (int y = 0; y < b.getHeight(); y++) 
    {
        for (int x = 0; x < b.getWidth(); x++) 
        {
            Candy* c = b.getCell(x, y);

            
            if (c == nullptr) 
            {
                std::cout << ". ";
            }
            else if (b.shouldExplode(x, y) == true) 
            {
                std::cout << "T "; // True: Va a explotar
            } 
            else 
            {
                std::cout << "F "; // False: Está a salvo
            }
        }
        std::cout << "\n"; 
    }
    std::cout << "\n\n\n";
}

bool test()
{
    // Test board 2D container
    Candy c(CandyType::TYPE_ORANGE);
    Board b(10, 10);
    b.setCell(&c, 0, 0);
    imprimirTablero(b);
    if (b.getCell(0, 0) != &c)
    {
        return false;
    }

    // Dump and load board
    {
        Board b2(10, 10);
        if (!b.dump(getDataDirPath() + "dump_board.txt"))
        {
            return false;
        }
        if (!b2.load(getDataDirPath() + "dump_board.txt"))
        {
            return false;
        }
        if (b2.getCell(0, 0)->getType() != c.getType())
        {
            return false;
        }
        std::filesystem::remove(getDataDirPath() + "dump_board.txt");
    }
    // Dump and load game
    /*{
        Game g;
        Controller cont;
        g.update(cont);
        if (!g.dump(getDataDirPath() + "dump_game.txt"))
        {
            return false;
        }
        Game g2;
        if (!g2.load(getDataDirPath() + "dump_game.txt"))
        {
            return false;
        }
        if (g != g2)
        {
            return false;
        }
        std::filesystem::remove(getDataDirPath() + "dump_game.txt");
    }
    */
    return true;
}

bool testShould()
{
    Candy c(CandyType::TYPE_ORANGE);
    Candy c2(CandyType::TYPE_PURPLE);
    Board b(10, 10);
    Board b2(10, 10);
    Board b3(10, 10);
    Board b4(10, 10);
    int x, y;
    //test para caramelos verticales
    for (y = 0; y < b.getHeight(); y++)
    {
        b.setCell(&c, 0, y);   
    }
    imprimirTablero(b);
    imprimirTableroBool(b);
    for(y = 0; y < b.getHeight(); y++)
    {
        if(b.shouldExplode(0,y) == false)
        {
            return false;
        }
    }
    for(y = 0; y < b.getHeight(); y++)
    {
        if(b.shouldExplode(1,y) == true)
        {
            return false;
        }
    }
    
    //test para caramelos horizontales

    for (x = 0; x < b2.getWidth(); x++)
    {
        b2.setCell(&c, x, 0);   
    }
    imprimirTablero(b2);
    for(x = 0; x < b2.getWidth(); x++)
    {
        if(b2.shouldExplode(x,0) == false)
        {
            return false;
        }
    }
    for(x = 0; x < b2.getWidth(); x++)
    {
        if(b2.shouldExplode(x,1) == true)
        {
            return false;
        }
    }

    //test para caramelos diagonales
    for (x = 0, y = 0; x < b3.getWidth() && y < b3.getHeight(); x++, y++)
    {
        b3.setCell(&c, x, y);   
    }
    imprimirTablero(b3);
    for(x = 0, y = 0; x < b3.getWidth() && y < b3.getHeight(); x++, y++)
    {
        if(b3.shouldExplode(x,y) == false)
        {
            return false;
        }
    }
    for(x = 1, y = 0; x < b3.getWidth() && y < b3.getHeight(); x++, y++)
    {
        if(b3.shouldExplode(x,y) == true)
        {
            return false;
        }
    }

    //test para caramelos diagonales2.0
    for (x = b4.getWidth()-1, y = 0; x >= 0 && y < b4.getHeight(); x--, y++)
    {
        b4.setCell(&c, x, y);   
    }
    imprimirTablero(b4);
    for(x = b4.getWidth()-1, y = 0; x >= 0 && y < b4.getHeight(); x--, y++)
    {
        if(b4.shouldExplode(x,y) == false)
        {
            return false;
        }
    }
    for(x = b4.getWidth()-1, y = 0; x >= 0 && y < b4.getHeight(); x--, y++)
    {
        if(b4.shouldExplode(x,y) == true)
        {
            return true;
        }
    }
    return true;
}

bool testBoard()
{
    Board b(DEFAULT_BOARD_HEIGHT, DEFAULT_BOARD_WIDTH);
    int i, j; 
    for(i = 0; i < DEFAULT_BOARD_HEIGHT; i++)
    {
        for(j = 0; j < DEFAULT_BOARD_WIDTH; j++)
        {
            if(b.getCell(j, i) != nullptr)
            {
                return false;
            }
        }
    }

    Candy c(CandyType::TYPE_ORANGE);

    for(i = 0; i < DEFAULT_BOARD_HEIGHT; i++)
    {
        for(j = 0; j < DEFAULT_BOARD_WIDTH; j++)
        {
            b.setCell(&c, j, i);
        }
    }

    return true; 
}

bool testGettersSetters()
{
    //getCell y setCell 

    Board b(10,10);
    Candy c(CandyType::TYPE_ORANGE);
    b.setCell(&c, 0, 0);
    if(b.getCell(0,0) != &c)
    {
        return false;
    }

    //getWidth y getHeight
    int boardWidth = b.getWidth();
    int boardHeight = b.getHeight();
    if(boardWidth != 10 || boardHeight != 10)
    {
        return false;
    }

    return true; 
}

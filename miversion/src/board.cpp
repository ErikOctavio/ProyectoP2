#include "board.h"
#include <memory>
#include <iostream>
#include <fstream>
using namespace std; 

Board::Board(int width, int height) : m_width(width), m_height(height)
{
    int i, j;

    for(i=0; i<height; i++)
    {

        vector<Candy*> filaTablero; 

        for(j=0; j<width; j++)
        {
            filaTablero.push_back(nullptr);
        }
        
        tablero.push_back(filaTablero);

    }
}

Board::~Board()
{
    
}

Candy* Board::getCell(int x, int y) const
{
    if (x >= 0 && x < m_width && y >= 0 && y < m_height)
    {
		return tablero[y][x];
    }
    return nullptr;
}

void Board::setCell(Candy* candy, int x, int y)
{
    if (x >= 0 && x < m_width && y >= 0 && y < m_height)
    {
		tablero[y][x] = candy;
    }
    return;
}

int Board::getWidth() const
{
    return m_width;
}

int Board::getHeight() const
{
    return m_height; 
}

bool Board::shouldExplode(int x, int y) const
{
    if (getCell(x, y) == nullptr)
    {
        return false;
	}

    int i;
    bool explode = false;
    bool nul = false; 
    bool coincidence = false; 

    if (tablero[y][x] == nullptr) 
    {
        nul = true;
    }

    int contador = 1;

    //Lo proximo es para hacer comprovaciones de si el caramelo deberia de explotar horizontalmente.
    if(nul == false)
    {
        for(i=1; x+i<m_width && coincidence == false; i++)
        {
            if(tablero[y][x+i] == nullptr  || tablero[y][x]->getType() != tablero[y][x+i]->getType())
            {
                coincidence = true;
            }
            else
            {
              contador += 1; 
            }
        }
    
        coincidence = false;
        for(i=1; x-i>=0 && coincidence == false; i++)
        {
            if(tablero[y][x-i] == nullptr || tablero[y][x]->getType() != tablero[y][x-i]->getType())
            {
                coincidence = true;
            }
            else
            {
                contador += 1; 
            }
        }

        if(contador >= SHORTEST_EXPLOSION_LINE)
        {
            explode = true;
        }

        contador = 1; 
        coincidence = false;

    //Lo proximo es para hacer comprovaciones de si el caramelo deberia de explotar verticalmente.

        for(i=1; y+i<m_height && coincidence == false && explode != true; i++)
        {
            if(tablero[y+i][x] == nullptr || tablero[y][x]->getType() != tablero[y+i][x]->getType())
            {
                coincidence = true;
            }
            else
            {
                contador += 1; 
            }
        
        } 

        coincidence = false;
        for(i=1; y-i>=0 && coincidence == false && explode != true; i++)
        {
            if(tablero[y-i][x] == nullptr || tablero[y][x]->getType() != tablero[y-i][x]->getType())
            {
                coincidence = true;
            }
            else
            {
                contador += 1; 
            }
        }

        if(contador >= SHORTEST_EXPLOSION_LINE)
        {
            explode = true;
        }

        contador = 1; 
        coincidence = false; 

    //Lo proximo es para hacer comprovaciones de si el caramelo deberia de explotar diagonalmente.

    //diagonales abajo derecha - arriba izquierda

        for(i=1; y+i<m_height && x+i<m_width && coincidence == false && explode != true; i++)
        {
            if(tablero[y+i][x+i] == nullptr || tablero[y][x]->getType() != tablero[y+i][x+i]->getType())
            {
                coincidence = true;
            }
            else
            { 
                contador += 1; 
            }
        }

        coincidence = false;
        for(i=1; y-i>=0 && x-i>=0 && coincidence == false && explode != true; i++)
        {
            if(tablero[y-i][x-i] == nullptr || tablero[y][x]->getType() != tablero[y-i][x-i]->getType())
            {
                coincidence = true;
            }
            else
            { 
                contador += 1; 
            }
        }

        if(contador >= SHORTEST_EXPLOSION_LINE)
        {
            explode = true;
        }

        contador = 1;
        coincidence = false;
    //diagonales abajo izquierda - arriba derecha

        for(i=1; y+i<m_height && x-i>=0 && coincidence == false && explode != true; i++)
        {
            if(tablero[y+i][x-i] == nullptr || tablero[y][x]->getType() != tablero[y+i][x-i]->getType())
            {
                coincidence = true;
            }
            else
            { 
                contador += 1; 
            }
        }

        coincidence = false;
        for(i=1; y-i>=0 && x+i<m_width && coincidence == false && explode != true; i++)
        {
            if(tablero[y-i][x+i] == nullptr || tablero[y][x]->getType() != tablero[y-i][x+i]->getType())
            {
                coincidence = true;
            }
            else
            {  
                contador += 1; 
            }
        }

        if(contador >= SHORTEST_EXPLOSION_LINE)
        {
            explode = true;
        }
         
    }

    return explode; 

    }
    
std::vector<Candy*> Board::explodeAndDrop()
{
    std::vector<Candy*> exploded;
    bool explosion_happened = true;
    // Matriz bool para marcar cuales van a explotar
    std::vector<std::vector<bool>> matriz;
    for (int y = 0; y < m_height; y++)
    {
        std::vector<bool> rows;
        for (int x = 0; x < m_width; x++)
        {
            rows.push_back(false);
        }
        matriz.push_back(rows);
    }
    while (explosion_happened)
    {
        explosion_happened = false;
        // Marcar las que van a explotar
        for (int y = 0; y < m_height; ++y)
        {
            for (int x = 0; x < m_width; ++x)
            {
                if (shouldExplode(x, y))
                {
                    matriz[y][x] = true;
                    explosion_happened = true;
                }
            }
        }
        // mover las que explotan a un vector y poner nullptr en el tablero
        for (int y = 0; y < m_height; ++y)
        {
            for (int x = 0; x < m_width; ++x)
            {
                if (matriz[y][x])
                {
                    Candy* c = getCell(x, y);
                    exploded.push_back(c);
                    setCell(nullptr, x, y);
                }
            }
        }
        // Dejar caer las piezas
        bool needs_drops = true;
        while (needs_drops)
        {
            needs_drops = false;
            for (int y = 1; y < m_height; ++y)
            {
                for (int x = 0; x < m_width; ++x)
                {
                    if (tablero[y][x] == nullptr && tablero[y - 1][x] != nullptr)
                    {
                        needs_drops = true;
                        tablero[y][x] = tablero[y - 1][x];
                        setCell(nullptr, x, y - 1);
                    }
                }
            }
        }
        // Reiniciar matriz para la siguiente iteración
        for (int y = 0; y < m_height; ++y)
        {
            for (int x = 0; x < m_width; ++x)
            {
                matriz[y][x] = false;
            }
        }
    }
    return exploded;
}

bool Board::dump(const std::string& output_path) const
{
    
    ofstream dumpFitxer;
    int i, j;
    dumpFitxer.open(output_path);

    if(dumpFitxer.is_open())
    {
        
        dumpFitxer << m_height << " " << m_width << "\n";

        for (int i = 0; i < m_height; i++)
        {
            for (int j = 0; j < m_width; j++)
            {
                Candy* caramelo = getCell(j, i);
                if (caramelo == nullptr)
                {
                    dumpFitxer << ". ";
                }
                else
                {
                    switch (caramelo->getType())
                    {
                        case CandyType::TYPE_RED:    dumpFitxer << "R "; break;
                        case CandyType::TYPE_GREEN:  dumpFitxer << "G "; break;
                        case CandyType::TYPE_YELLOW: dumpFitxer << "Y "; break;
                        case CandyType::TYPE_BLUE:   dumpFitxer << "B "; break;
                        case CandyType::TYPE_PURPLE: dumpFitxer << "P "; break;
                        case CandyType::TYPE_ORANGE: dumpFitxer << "O "; break;
                    }
                }
            }
            dumpFitxer << "\n";
        }

    dumpFitxer.close();
    return true;
    }
    else
    {
        return false;
    }
    

}

bool Board::load(const std::string& input_path)
{
    ifstream loadFitxer;
    loadFitxer.open(input_path);

    int i, j;

    if(loadFitxer.is_open())
    {

        int file_width, file_height;
        loadFitxer >> file_width >> file_height;

        for (i = 0; i < m_height; i++)
        {
            for (j = 0; j < m_width; j++)
            {
                tablero[i][j] = nullptr;
            }
        }

        char letraCaramelo;

        for (i = 0; i < m_height; i++)
        {
            for (j = 0; j < m_width; j++)
            {
                loadFitxer >> letraCaramelo;

                if (letraCaramelo == '.')
                {
                    tablero[i][j] = nullptr;
                }
                else
                {
                    switch (letraCaramelo)
                    {
                        case 'R': tablero[i][j] = &m_rojo; break;
                        case 'G': tablero[i][j] = &m_verde; break;
                        case 'Y': tablero[i][j] = &m_amarillo; break;
                        case 'B': tablero[i][j] = &m_azul; break;
                        case 'P': tablero[i][j] = &m_morado; break;
                        case 'O': tablero[i][j] = &m_naranja; break;
                        default:  tablero[i][j] = nullptr; break;
                    }
                }
            }
        }
        loadFitxer.close();
        return true;
    }
    else 
    {
        return false;
    }

    
}

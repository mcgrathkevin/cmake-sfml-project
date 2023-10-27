#include <SFML/Graphics.hpp>
#include "snake.h"

int main()
{
    // play the game 
    Snake snake(sf::Vector2f(127, 127), 9); 
    return snake.run(); 
}

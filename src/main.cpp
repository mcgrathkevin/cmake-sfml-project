#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Particles.h"
#include "Snake.h"

/*
    SNAKE
*/
int main()
{
    // play the game 
    Snake snake(sf::Vector2f(127, 127), 3); 
    return snake.run(); 
}

/*
    THREADING 
*/
// void renderingThread(sf::RenderWindow* window)
// {
//     // activate the window's context
//     window->setActive(true);

//     // the rendering loop
//     while (window->isOpen())
//     {
//         // clear the window with black color
//         window->clear(sf::Color::Black);

//         // draw everything here...
//         window->draw(getTriangle());
        
//         // end the current frame
//         window->disrun();
//     }
// }

// int main()
// {
//     // create the window
//     sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

//     // deactivate its OpenGL context
//     window.setActive(false);

//     // launch the rendering thread
//     sf::Thread thread(&renderingThread, &window);
//     thread.launch();

//     // run the program as long as the window is open
//     while (window.isOpen())
//     {
//         // check all the window's events that were triggered since the last iteration of the loop
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             // "close requested" event: we close the window
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }
//     }

//     return 0;
// }


/* 
    TILE MAP
*/
// int main()
// {
//     // create the window
//     sf::RenderWindow window(sf::VideoMode(512, 256), "Tilemap");

//     // define the level with an array of tile indices
//     const int level[] =
//     {
//         0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//         0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
//         1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
//         0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
//         0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
//         0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
//         2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
//         0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
//     };

//     // create the tilemap from the level definition
//     TileMap map;
//     if (!map.load("tileset.png", sf::Vector2u(32, 32), level, 16, 8))
//         return -1;

//     // run the main loop
//     while (window.isOpen())
//     {
//         // handle events
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if(event.type == sf::Event::Closed)
//                 window.close();
//         }

//         // draw the map
//         window.clear();
//         window.draw(map);
//         window.disrun();
//     }

//     return 0;
// }

/*
    PARTICLE SYSTEM
*/
// int main()
// {
//     // create the window
//     sf::RenderWindow window(sf::VideoMode(512, 256), "Particles");

//     // create the particle system
//     ParticleSystem particles(1000);

//     // create a clock to track the elapsed time
//     sf::Clock clock;

//     // run the main loop
//     while (window.isOpen())
//     {
//         // handle events
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if(event.type == sf::Event::Closed)
//                 window.close();
//         }

//         // make the particle system emitter follow the mouse
//         sf::Vector2i mouse = sf::Mouse::getPosition(window);
//         particles.setEmitter(window.mapPixelToCoords(mouse));

//         // update it
//         sf::Time elapsed = clock.restart();
//         particles.update(elapsed);

//         // draw it
//         window.clear();
//         window.draw(particles);
//         window.disrun();
//     }

//     return 0;
// }
#pragma once
#include <iostream>
#include <deque>
#include <SFML/Graphics.hpp>
#include "block.h"

constexpr int WINDOW_WIDTH = 256;
constexpr int WINDOW_HEIGHT = 256;
constexpr float BLOCK_SIZE = 14.0f;
constexpr float BLOCK_SPACING = 2.0f;
const float BLOCK_OFFSET = BLOCK_SIZE + BLOCK_SPACING;
const int NUM_BLOCKS = (int)(WINDOW_WIDTH / BLOCK_OFFSET);

enum direction_t {NORTH, EAST, SOUTH, WEST, NONE};

class Snake : public sf::Drawable {
public:

  Snake();
  Snake(sf::Vector2f pos, int snakeSize);
  ~Snake();

  int run();
  

private:
  sf::RenderWindow app_;
  std::vector<std::vector<int>> board_; 
  sf::Vector2i head_;
  sf::Vector2i apple_;
  sf::Text score_;
  direction_t direction_;
  // TODO: Just use math to move snake in a grid-like manner:
  // - set window dimensions
  // - match speed of snake with 1 grid per tick 
  // - determine rect_;size (pixels) by window size / #blocks
  void update(sf::Time delta);
  void processEvents();
  void render();
  bool checkCollision() const;
  
  void moveSnake(int dX, int dY);
  void removeTail();
  void lerp(Block& src, Block& dest, float delta);
  // void lerp(Block& src, turn_t& dest, float delta);
  // bool isAtTurn(rect_;thisBlock, turn_t thisTurn) const;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
    // our particles don't use a texture
    states.texture = NULL;

    // draw the vertex array
    int i = 0;
    int j = 0;
    for (int i = 0; i < NUM_BLOCKS; i++) 
      for (int j = 0; j < NUM_BLOCKS; j++) 
        if (board_[i][j] > 0)
          target.draw(Block(i*BLOCK_OFFSET, j*BLOCK_OFFSET));
        else if (board_[i][j] == -1)
          target.draw(Block(i*BLOCK_OFFSET, j*BLOCK_OFFSET, sf::Color::Red));
  }

  void show() const {
    std::cout << "Displaying board" << std::endl;
    for (const auto& row : board_) {
      for (const auto& col : row)
        std::cout << col << " "; 
      std::cout << "\n";
    }
  }
};
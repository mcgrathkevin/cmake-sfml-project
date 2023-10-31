#pragma once
#include <iostream>
#include <deque>
#include <SFML/Graphics.hpp>
#include "block.h"

#define EMPTY 0
#define APPLE -1

constexpr int WINDOW_WIDTH = 512;
constexpr int WINDOW_HEIGHT = 512;
constexpr float BLOCK_SIZE = 14.0f;
constexpr float BLOCK_SPACING = 2.0f;
const float BLOCK_CELL = BLOCK_SIZE + BLOCK_SPACING;
const int NUM_BLOCKS = (int)(WINDOW_WIDTH / BLOCK_CELL);

enum direction_t {NORTH, EAST, SOUTH, WEST};

class Snake : public sf::Drawable {
public:

  Snake();
  Snake(sf::Vector2f pos, int snakeSize_);
  ~Snake();

  int run();
  

private:
  sf::RenderWindow app_;
  std::vector<std::vector<int>> board_; 
  std::vector<Block> body_;
  sf::Vector2i head_;
  sf::Vector2i apple_;
  unsigned score_;
  direction_t direction_;
  int snakeSize_;
  bool gameOver_;
  // TODO: Just use math to move snake in a grid-like manner:
  // - set window dimensions
  // - match speed of snake with 1 grid per tick 
  // - determine rect_;size (pixels) by window size / #blocks
  void update_(sf::Time delta);
  void processEvents_();
  void render_();
  
  void moveSnake_();
  void getBlocks_();
  void removeTail_();
  void lerp_(Block& src, Block& dest, float delta);
  // void lerp_(Block& src, turn_t& dest, float delta);
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
        if (board_[i][j] > EMPTY)
          target.draw(Block(i*BLOCK_CELL, j*BLOCK_CELL));
        else if (board_[i][j] == -1)
          target.draw(Block(i*BLOCK_CELL, j*BLOCK_CELL, sf::Color::Red));
  }

  void show_() const {
    std::cout << "Displaying board" << std::endl;
    for (const auto& row : board_) {
      for (const auto& col : row)
        std::cout << col << " "; 
      std::cout << "\n";
    }
  }
};
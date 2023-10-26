#pragma once
#include <iostream>
#include <deque>
#include <SFML/Graphics.hpp>
#include "block.h"

constexpr int WINDOW_WIDTH = 256;
constexpr int WINDOW_HEIGHT = 256;
constexpr float BLOCK_SIZE = 16.0f;
constexpr float BLOCK_SPACING = 2.0f;
const float BLOCK_OFFSET = BLOCK_SIZE + BLOCK_SPACING;

enum direction_t {NORTH, EAST, SOUTH, WEST, NONE};
using turn_t = std::pair<direction_t, sf::Vector2f>;

class Snake : public sf::Drawable {
public:

  Snake();
  Snake(sf::Vector2f pos, int snakeSize);
  ~Snake();

  int run();
  

private:
  sf::RenderWindow app_;
  std::vector<Block> player_;
  Block apple_;
  sf::Text score_;
  direction_t direction_;
  std::deque<turn_t> turns_;
  // TODO: Just use math to move snake in a grid-like manner:
  // - set window dimensions
  // - match speed of snake with 1 grid per tick 
  // - determine block size (pixels) by window size / #blocks
  void update(sf::Time delta);
  void processEvents();
  void render();
  bool checkCollision() const;
  void lerp(Block& src, Block& dest, float delta);
  void lerp(Block& src, turn_t& dest, float delta);
  bool isAtTurn(Block thisBlock, turn_t thisTurn) const;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
    // our particles don't use a texture
    states.texture = NULL;

    // draw the vertex array
    for (const auto& block : player_) 
      target.draw(block);
  }
};
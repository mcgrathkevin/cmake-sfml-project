#include "block.h"
#include "snake.h"

Block::Block() :
  position_(sf::Vector2f()),
  width_(BLOCK_CELL),
  height_(BLOCK_CELL),
  color_(sf::Color::Green)
{
  rect_.setSize(sf::Vector2f(width_, height_));
  rect_.setFillColor(color_);
  rect_.setPosition(position_);
}

Block::Block(float startX, float startY) :
  width_(BLOCK_CELL),
  height_(BLOCK_CELL),
  color_(sf::Color::Green)
{
  position_.x = startX;
  position_.y = startY;

  rect_.setSize(sf::Vector2f(width_, height_));
  rect_.setFillColor(color_);
  rect_.setPosition(position_);
}

Block::Block(float startX, float startY, sf::Color color) :
  width_(BLOCK_CELL),
  height_(BLOCK_CELL),
  color_(color)
{
  position_.x = startX;
  position_.y = startY;

  rect_.setSize(sf::Vector2f(width_, height_));
  rect_.setFillColor(color_);
  rect_.setPosition(position_);
}

Block::Block(sf::Vector2f position) :
  position_(position),
  width_(BLOCK_CELL),
  height_(BLOCK_CELL),
  color_(sf::Color::Green)
{
  rect_.setSize(sf::Vector2f(width_, height_));
  rect_.setFillColor(color_);
  rect_.setPosition(position_);
}

Block::Block(sf::Vector2f position, sf::Color color) :
  position_(position),
  width_(BLOCK_CELL),
  height_(BLOCK_CELL),
  color_(color)
{
  rect_.setSize(sf::Vector2f(width_, height_));
  rect_.setFillColor(color_);
  rect_.setPosition(position_);
}

Block::Block(float startX, float startY, float newWidth, float newheight_, const sf::Color newcolor) :
  width_(newWidth),
  height_(newheight_),
  color_(newcolor)
{
  position_.x = startX;
  position_.y = startY;

  rect_.setSize(sf::Vector2f(width_, height_));
  rect_.setFillColor(color_);
  rect_.setPosition(position_);
}

Block::~Block() {
}
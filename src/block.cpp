#include "block.h"

Block::Block() :
  position(sf::Vector2f()),
  width(40.0f),
  height(20.0f),
  color(sf::Color::Green)
{
  block.setSize(sf::Vector2f(width, height));
  block.setFillColor(color);
  block.setPosition(position);
}

Block::Block(float startX, float startY) :
  width(25.0f),
  height(20.0f),
  color(sf::Color::Green)
{
  position.x = startX;
  position.y = startY;

  block.setSize(sf::Vector2f(width, height));
  block.setFillColor(color);
  block.setPosition(position);
}

Block::Block(float startX, float startY, float newWidth, float newHeight, const sf::Color newColor) :
  width(newWidth),
  height(newHeight),
  color(newColor)
{
  position.x = startX;
  position.y = startY;

  block.setSize(sf::Vector2f(width, height));
  block.setFillColor(color);
  block.setPosition(position);
}

Block::~Block() {
}
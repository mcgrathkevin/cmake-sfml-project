#pragma once
#include <SFML/Graphics.hpp>

class Block : public sf::Drawable {
public:

  // add functions to play with the entity's geometry / colors / texturing...
  Block();
  Block(float x, float y);
  Block(float startX, float startY, const float newWidth, const float newHeight, const sf::Color newColor); 
  virtual ~Block();

  float getX() const { return position.x; }
  float getY() const { return position.y; }
  sf::Vector2f getPos() const {return position; }
  void setPos(sf::Vector2f newPos) { position = newPos; block.setPosition(newPos); }
  void setX(float x) { position.x = x; block.setPosition(position); }
  void setY(float y) { position.y = y; block.setPosition(position); }

private:

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(block);
  }

  sf::RectangleShape block;
  sf::Vector2f position;
  float width, height;
  sf::Color color;
};
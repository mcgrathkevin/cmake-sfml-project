#pragma once
#include <SFML/Graphics.hpp>

class Block : public sf::Drawable {
public:

  // add functions to play with the entity's geometry / colors / texturing...
  Block();
  Block(float x, float y);
  Block(float startX, float startY, sf::Color color);
  Block(sf::Vector2f position); 
  Block(sf::Vector2f position, sf::Color color); 
  Block(float startX, float startY, const float newWidth, const float newHeight, const sf::Color newColor); 
  virtual ~Block();

  float getX() const { return position_.x; }
  float getY() const { return position_.y; }
  sf::Vector2f getPos() const {return position_; }
  void setPos(sf::Vector2f newPos) { position_ = newPos; rect_.setPosition(newPos); }
  void setX(float x) { position_.x = x; rect_.setPosition(position_); }
  void setY(float y) { position_.y = y; rect_.setPosition(position_); }

private:

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(rect_);
  }

  sf::RectangleShape rect_;
  sf::Vector2f position_;
  float width_, height_;
  sf::Color color_;
};
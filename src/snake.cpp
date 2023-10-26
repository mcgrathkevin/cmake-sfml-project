#include "snake.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

Snake::Snake() {
}

Snake::Snake(sf::Vector2f pos, int snakeSize) :
  app_(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "I don't fw snakes mane"),
  direction_(NONE) {

  // Initalize snake
  if (snakeSize > 0) {
    float x = pos.x;
    float y = pos.y;

    for (size_t i = 0; i < snakeSize; i ++) {
      player_.push_back(Block(x, y, BLOCK_SIZE, BLOCK_SIZE, sf::Color::Green));
      x -= BLOCK_SIZE + BLOCK_SPACING;
    }

    turns_.resize(snakeSize);
  }

  // Initialize apple
  float appleX = std::rand() % WINDOW_WIDTH;
  float appleY = std::rand() % WINDOW_HEIGHT;

  apple_ = Block(appleX, appleY, BLOCK_SIZE, BLOCK_SIZE, sf::Color::Red);
}

Snake::~Snake() {} 

void Snake::update(sf::Time delta) {
  Block oldHead = player_.front();

  float playerX = oldHead.getX();
  float playerY = oldHead.getY();\
  
  // account for delta of update function call
  float moveDelta = 4*BLOCK_SIZE * delta.asSeconds();

  switch (direction_) {
    case NORTH: 
      playerY -= moveDelta;
      if (playerY <= 0) playerY = WINDOW_HEIGHT - BLOCK_SIZE;
      break;
    case SOUTH:
      playerY += moveDelta;
      if (playerY >= WINDOW_HEIGHT) playerY = BLOCK_SIZE;
      break;
    case EAST:
      playerX += moveDelta;
      if (playerX >= WINDOW_WIDTH) playerX = BLOCK_SIZE;
      break;
    case WEST:
      playerX -= moveDelta;
      if (playerX <= 0) playerX = WINDOW_WIDTH - BLOCK_SIZE;
      break;
    case NONE:
      break;
  }

  if (direction_ != NONE) {
    turns_.push_front(turn_t(direction_, sf::Vector2f(playerX, playerY)));
    for (auto t : turns_) {
      if (isAtTurn(player_.back(), t))
        turns_.pop_back();
    }
    for (int i = player_.size()-1; i > 0; i--) {
      int turnIndex = turns_.size()-1;
      if (i < turns_.size())
        turnIndex = i - 1;
      if (turns_.empty())
        lerp(player_[i], player_[i-1], delta.asSeconds());
      else {
        lerp(player_[i], turns_[turnIndex], delta.asSeconds());
      }
        
      // std::cout << i << ": " << player_[i].getPos().x << " " << player_[i].getPos().y << std::endl;
      std::cout << turns_.size();
      // sf::sleep(sf::milliseconds(50));
    }
    std::cout << "0: " << player_[0].getPos().x << " " << player_[0].getPos().y << std::endl;
    player_[0].setPos(sf::Vector2f(playerX, playerY));
  }



}

bool Snake::checkCollision() const {
  return true;
}


bool Snake::isAtTurn(Block thisBlock, turn_t thisTurn) const {
  float blockX = thisBlock.getX();
  float blockY = thisBlock.getY();
  float turnX = thisTurn.second.x;
  float turnY = thisTurn.second.y;

  if (thisTurn.first == NORTH || thisTurn.first == SOUTH)
    return blockY == turnY;
  else 
    return blockX == turnX;
}

void Snake::lerp(Block& src, Block& dest, float delta) {
  src.setPos(src.getPos() + ((dest.getPos() - src.getPos()) * delta));
}

void Snake::lerp(Block& src, turn_t& dest, float delta) {
  src.setPos(src.getPos() + ((dest.second - src.getPos()) * delta));
}

void Snake::processEvents() {
  sf::Event event;

  while (app_.pollEvent(event)) {
    if(event.type == sf::Event::Closed)
      app_.close();
    // Use if instead of else-if in case 2 keys pressed same time 
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && direction_ != SOUTH) 
      direction_ = NORTH;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && direction_ != NORTH) 
      direction_ = SOUTH;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && direction_ != WEST) 
      direction_ = WEST;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && direction_ != EAST) 
      direction_ = EAST;
  }
}

void Snake::render() {
  app_.clear();
  app_.draw(*this);
  app_.draw(apple_);
  app_.display();
}

// create a clock to track the elapsed time
int Snake::run() {
    
    app_.setFramerateLimit(60);
    sf::Clock clock; 
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    // 60 fps
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    // run the main loop
    while (app_.isOpen())
    {
      processEvents();
      timeSinceLastUpdate += clock.restart();
      while (timeSinceLastUpdate > TimePerFrame) {
        timeSinceLastUpdate -= TimePerFrame;
        processEvents();
        update(TimePerFrame);
      }
      render();
    }
    
    return 0;
}
#include "snake.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

Snake::Snake() {
}

Snake::Snake(sf::Vector2f pos, int snakeSize) :
  app_(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "I don't fw snakes mane"),
  direction_(NONE) {

  uint8_t bodyCount = 1;
  board_.resize(NUM_BLOCKS);
  
  // Initialize board
  for (int i = 0; i < NUM_BLOCKS; i++) 
    for (int j = 0; j < NUM_BLOCKS; j++) 
      board_[i].push_back(0);
  
  // If we store head loc initially and always update it we never need to iterate looking for it
  head_ = sf::Vector2i(NUM_BLOCKS/2, NUM_BLOCKS/2);

  board_[NUM_BLOCKS/2][NUM_BLOCKS/2] = snakeSize;
  board_[NUM_BLOCKS/2][NUM_BLOCKS/2-1] = snakeSize-1;
  board_[NUM_BLOCKS/2][NUM_BLOCKS/2-2] = snakeSize-2;
  board_[NUM_BLOCKS/2][NUM_BLOCKS/2-3] = snakeSize-3;
  board_[NUM_BLOCKS/2][NUM_BLOCKS/2-4] = snakeSize-4;
  board_[NUM_BLOCKS/2-1][NUM_BLOCKS/2-4] = snakeSize-5;
  board_[NUM_BLOCKS/2-2][NUM_BLOCKS/2-4] = snakeSize-6;
  board_[NUM_BLOCKS/2-3][NUM_BLOCKS/2-4] = snakeSize-7;
  board_[NUM_BLOCKS/2-3][NUM_BLOCKS/2-5] = snakeSize-8;

  show();

  // Initialize apple
  apple_.x = std::rand() % NUM_BLOCKS;
  apple_.y = std::rand() % NUM_BLOCKS;

  board_[apple_.x][apple_.y] = -1;
}

void Snake::moveSnake(int dX, int dY) {
  1
}

void Snake::removeTail() {
  for (int i = 0; i < NUM_BLOCKS; i++) 
    for (int j = 0; j < NUM_BLOCKS; j++) 
      if (board_[i][j] < 0)
        board_[i][j] -= 1;
}

Snake::~Snake() {} 

void Snake::update(sf::Time delta) {

  
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

}

bool Snake::checkCollision() const {
  return true;
}


// bool Snake::isAtTurn(rect_;thisBlock, turn_t thisTurn) const {
//   float blockX = thisBlock.getX();
//   float blockY = thisBlock.getY();
//   float turnX = thisTurn.second.x;
//   float turnY = thisTurn.second.y;

//   if (thisTurn.first == NORTH || thisTurn.first == SOUTH)
//     return blockY == turnY;
//   else 
//     return blockX == turnX;
// }

void Snake::lerp(Block& src, Block& dest, float delta) {
  src.setPos(src.getPos() + ((dest.getPos() - src.getPos()) * delta));
}

// void Snake::lerp(Block& src, turn_t& dest, float delta) {
//   src.setPos(src.getPos() + ((dest.second - src.getPos()) * delta));
// }

void Snake::processEvents() {
  sf::Event event;

  while (app_.pollEvent(event)) {
    if(event.type == sf::Event::Closed)
      app_.close();
    // Use if instead of else-if in case 2 keys pressed same time 
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && direction_ != SOUTH) 
      direction_ = NORTH;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && direction_ != NORTH) 
      direction_ = SOUTH;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && direction_ != WEST) 
      direction_ = WEST;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && direction_ != EAST) 
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
        // update(TimePerFrame);
      }
      render();
    }
    
    return 0;
}
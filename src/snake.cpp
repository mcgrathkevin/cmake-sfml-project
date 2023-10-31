#include "snake.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

Snake::Snake() {
}

Snake::Snake(sf::Vector2f pos, int snakeSize) :
  app_(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "I don't fw snakes mane"),
  direction_(EAST), snakeSize_(snakeSize), gameOver_(false) {

  uint8_t bodyCount = 1;
  board_.resize(NUM_BLOCKS);
  
  // Initialize board
  for (int i = 0; i < NUM_BLOCKS; i++) 
    for (int j = 0; j < NUM_BLOCKS; j++) 
      board_[i].push_back(0);
  
  // If we store head loc initially and always update it we never need to iterate looking for it
  head_ = sf::Vector2i(NUM_BLOCKS/2, NUM_BLOCKS/2);

  board_[NUM_BLOCKS/2][NUM_BLOCKS/2] = snakeSize_;
  board_[NUM_BLOCKS/2][NUM_BLOCKS/2-1] = snakeSize_-1;
  board_[NUM_BLOCKS/2][NUM_BLOCKS/2-2] = snakeSize_-2;
  board_[NUM_BLOCKS/2][NUM_BLOCKS/2-3] = snakeSize_-3;
  board_[NUM_BLOCKS/2][NUM_BLOCKS/2-4] = snakeSize_-4;
  board_[NUM_BLOCKS/2-1][NUM_BLOCKS/2-4] = snakeSize_-5;
  board_[NUM_BLOCKS/2-2][NUM_BLOCKS/2-4] = snakeSize_-6;
  board_[NUM_BLOCKS/2-3][NUM_BLOCKS/2-4] = snakeSize_-7;
  board_[NUM_BLOCKS/2-3][NUM_BLOCKS/2-5] = snakeSize_-8;

  show_();

  // Initialize apple 
  do {
    apple_.x = std::rand() % NUM_BLOCKS;
    apple_.y = std::rand() % NUM_BLOCKS;

  } while (board_[apple_.x][apple_.y] != EMPTY);
  
    board_[apple_.x][apple_.y] = APPLE;
}

void Snake::moveSnake_() {
  switch (direction_) {
    case NORTH: 
      head_.y--;
      break;
    case SOUTH:
      head_.y++;
      break;
    case EAST:
      head_.x--;
      break;
    case WEST:
      head_.x++;
      break;
  }

  head_.x %= board_.size();
  head_.y %= board_.size();

  if (board_[head_.x][head_.y] == -1)
    score_++;
  else if (board_[head_.x][head_.y] != 0)
    gameOver_ = true;

  board_[head_.x][head_.y] = snakeSize_ + 1;

  removeTail_();

  show_();
}

void Snake::getBlocks_() {
  body_.resize(snakeSize_);

  int blockIndex = 0;

  for (int i = 0; i < NUM_BLOCKS; i++) 
    for (int j = 0; j < NUM_BLOCKS; j++) 
      if (board_[i][j] > EMPTY)
        body_[blockIndex] = Block(i*BLOCK_CELL, j*BLOCK_CELL, sf::Color::Green); 
  // TODO: IDEA - move snake  

}

void Snake::removeTail_() {
  for (int i = 0; i < NUM_BLOCKS; i++) 
    for (int j = 0; j < NUM_BLOCKS; j++) 
      if (board_[i][j] > 0)
        board_[i][j]--;
}

Snake::~Snake() {} 

void Snake::update_(sf::Time delta) {

  
  // account for delta of update function call
  float moveDelta = 4*BLOCK_SIZE * delta.asSeconds();

  moveSnake_();

  // switch (direction_) {
    // case NORTH: 
    //   playerY -= moveDelta;
    //   if (playerY <= 0) playerY = WINDOW_HEIGHT - BLOCK_SIZE;
    //   break;
    // case SOUTH:
    //   playerY += moveDelta;
    //   if (playerY >= WINDOW_HEIGHT) playerY = BLOCK_SIZE;
    //   break;
    // case EAST:
    //   playerX += moveDelta;
    //   if (playerX >= WINDOW_WIDTH) playerX = BLOCK_SIZE;
    //   break;
    // case WEST:
    //   playerX -= moveDelta;
    //   if (playerX <= 0) playerX = WINDOW_WIDTH - BLOCK_SIZE;
    //   break;
    // case NONE:
    //   break;
  // }

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

void Snake::lerp_(Block& src, Block& dest, float delta) {
  src.setPos(src.getPos() + ((dest.getPos() - src.getPos()) * delta));
}

// void Snake::lerp_(Block& src, turn_t& dest, float delta) {
//   src.setPos(src.getPos() + ((dest.second - src.getPos()) * delta));
// }

void Snake::processEvents_() {
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

void Snake::render_() {
  app_.clear();
  app_.draw(*this);
  app_.display();
}

// create a clock to track the elapsed time
int Snake::run() {
    
    sf::Clock clock; 
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    // 60 fps
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    // run the main loop
    while (app_.isOpen() && !gameOver_)
    {
      processEvents_();
      timeSinceLastUpdate += clock.restart();
      while (timeSinceLastUpdate > TimePerFrame) {
        timeSinceLastUpdate -= TimePerFrame;
        processEvents_();
        update_(TimePerFrame);
      }
      render_();
    }
    
    return 0;
}
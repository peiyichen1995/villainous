#include "object/Player.h"
#include <iostream>

Player::Player(const std::string &name) : name(name) {}

void Player::chooseVillain(
    UniqueVector<Villain> &villains,
    std::unordered_map<std::string, std::unique_ptr<Villain>> &controls) {
  std::string villain;
  utils::requestUserInput(
      villain, name, ", please choose from the following villains: ", villains);
  controls[name] = villains.pop(villain);
}
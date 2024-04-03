#include "object/Player.h"
#include <iostream>

Player::Player(const YAML::Node &node)
    : name(node["name"].as<std::string>()), id(node["id"].as<unsigned int>()) {}

void Player::chooseVillain(
    UniqueVector<Villain> &villains,
    std::unordered_map<std::string, std::unique_ptr<Villain>> &controls) {
  std::string villain;
  utils::requestUserInputLine(
      villain, name, ", please choose from the following villains: ", villains);
  controls[name] = villains.pop(villain);
}
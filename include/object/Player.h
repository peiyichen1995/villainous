#pragma once

#include "object/Villain.h"
#include "utils/IO.h"
#include "utils/UniqueVector.h"
#include <memory>
#include <string>
#include <unordered_map>

class Player {
public:
  Player(const YAML::Node &node);
  void chooseVillain(
      UniqueVector<Villain> &villains,
      std::unordered_map<std::string, std::unique_ptr<Villain>> &controls);
  const std::string name;
  const unsigned int id;
};
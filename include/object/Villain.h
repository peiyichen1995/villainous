#pragma once

#include "yaml.h"
#include <string>

class Villain {
public:
  Villain(const YAML::Node &node);
  const std::string name;
  int power;
};
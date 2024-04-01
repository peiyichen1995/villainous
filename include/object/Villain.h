#pragma once

#include <string>

class Villain {
public:
  Villain(const std::string &);
  const std::string name;
  int power;
};
#include "object/Villain.h"

Villain::Villain(const YAML::Node &node)
    : name(node["name"].as<std::string>()), power(0) {}
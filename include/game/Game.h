#pragma once

#include "object/Player.h"
#include "object/Villain.h"
#include "utils/IO.h"
#include "utils/UniqueVector.h"
#include "yaml.h"
#include <filesystem>
#include <unordered_map>

class Game {
public:
  enum class State {
    // pre-game
    choose_villain,
    // in-game,
    pre_turn
  };

  Game();

  template <typename... T> void addPlayer(T... args) {
    auto p = std::make_unique<Player>(std::forward<T>(args)...);
    utils::log("LOG", "Player ", p->name, " joined the game.");
    _players.add(p);
  }

  void removePlayer(const std::string &name);

  void removeVillain(const std::string &name);

  void loadExtensions(const std::filesystem::path &path);

  void loadExtension(const std::filesystem::path &path);

  void loadVillains(const std::filesystem::path &path);

  void loadVillain(const YAML::Node &node);

  bool launch();

private:
  UniqueVector<Player> _players;
  UniqueVector<Villain> _villains;
  std::unordered_map<std::string, std::unique_ptr<Villain>> _controls;
  State _state;
};
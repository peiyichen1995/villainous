#pragma once

#include "object/Player.h"
#include "object/Villain.h"
#include "utils/IO.h"
#include "utils/UniqueVector.h"
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

  template <typename... T> void addVillain(T... args) {
    auto v = std::make_unique<Villain>(std::forward<T>(args)...);
    utils::log("LOG", "Villain ", v->name, " has been added to the game.");
    _villains.add(v);
  }

  void removeVillain(const std::string &name);

  bool launch();

private:
  UniqueVector<Player> _players;
  UniqueVector<Villain> _villains;
  std::unordered_map<std::string, std::unique_ptr<Villain>> _controls;
  State _state;
};
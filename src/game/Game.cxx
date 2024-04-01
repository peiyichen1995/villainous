#include "game/Game.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

Game::Game() : _state(State::choose_villain) {
  utils::log("GAME STATE", "CHOOSE VILLAIN");
}

void Game::removePlayer(const std::string &name) {
  _players.remove(name);
  utils::log("LOG", "Player ", name, " left the game.");
}

void Game::removeVillain(const std::string &name) {
  _villains.remove(name);
  utils::log("LOG", "Villain ", name, " has been removed from the game.");
}

bool Game::launch() {
  switch (_state) {

  case State::choose_villain:
    for (auto &p : _players)
      if (!_controls.count(p.name)) {
        p.chooseVillain(_villains, _controls);
        return true;
      }
    _state = State::pre_turn;
    utils::log("GAME STATE", "PRE TURN");
    return true;

  case State::pre_turn:
    return true;
  }

  throw std::invalid_argument("unknown state.");
}
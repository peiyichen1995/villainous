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

void Game::loadExtensions(const std::filesystem::path &path) {
  utils::log("LOG", "Loading extensions from ", path);
  for (const auto &entry : std::filesystem::directory_iterator(path))
    loadExtension(entry.path());
}

void Game::loadExtension(const std::filesystem::path &path) {
  utils::log("LOG", "Loading extension ", path.stem());
  loadVillains(path / "villains");
}

void Game::loadVillains(const std::filesystem::path &path) {
  for (const auto &entry : std::filesystem::recursive_directory_iterator(path))
    if (entry.path().extension() == ".yml") {
      YAML::Node config = YAML::LoadFile(entry.path());
      loadVillain(config);
    }
}

void Game::loadVillain(const YAML::Node &node) {
  auto v = std::make_unique<Villain>(node);
  utils::log("LOG", "Loaded villain ", v->name);
  _villains.add(v);
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
#include "game/Client.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

Client::Client() : _state(State::choose_villain) {
  utils::log("GAME STATE", "CHOOSE VILLAIN");
  _client = enet_host_create(NULL, 1, 1, 0, 0);
  if (!_client) {
    std::cerr << "An error occurred while trying to create an ENet client host."
              << std::endl;
    exit(EXIT_FAILURE);
  }
  utils::log("LOG", "Client created.");
}

Client::~Client() { enet_host_destroy(_client); }

void Client::connectToServer() {
  ENetAddress address;
  enet_address_set_host(&address, "127.0.0.1");
  address.port = 8000;

  _server = enet_host_connect(_client, &address, 1, 0);
  if (!_server) {
    std::cerr << "No available server for initiating an ENet connection."
              << std::endl;
    exit(EXIT_FAILURE);
  }

  /* Wait up to 5 seconds for the connection attempt to succeed. */
  ENetEvent event;
  if (enet_host_service(_client, &event, 5000) > 0 &&
      event.type == ENET_EVENT_TYPE_CONNECT) {
    enet_host_flush(_client);
    utils::log("LOG", "Connection to 127.0.0.1:8000 succeeded.");
  } else {
    /* Either the 5 seconds are up or a disconnect event was */
    /* received. Reset the server in the event the 5 seconds   */
    /* had run out without any significant event.            */
    enet_peer_reset(_server);
    std::cerr << "Connection to 127.0.0.1:8000 failed" << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Client::removePlayer(const std::string &name) {
  _players.remove(name);
  utils::log("LOG", "Player ", name, " left the game.");
}

void Client::loadPlayer(const std::filesystem::path &path) {
  utils::log("LOG", "Loading account information from ", path);
  YAML::Node config = YAML::LoadFile(path);
  auto p = std::make_unique<Player>(config);
  _players.add(p);
}

void Client::removeVillain(const std::string &name) {
  _villains.remove(name);
  utils::log("LOG", "Villain ", name, " has been removed from the game.");
}

void Client::loadExtensions(const std::filesystem::path &path) {
  utils::log("LOG", "Loading extensions from ", path);
  for (const auto &entry : std::filesystem::directory_iterator(path))
    loadExtension(entry.path());
}

void Client::loadExtension(const std::filesystem::path &path) {
  utils::log("LOG", "Loading extension ", path.stem());
  loadVillains(path / "villains");
}

void Client::loadVillains(const std::filesystem::path &path) {
  for (const auto &entry : std::filesystem::recursive_directory_iterator(path))
    if (entry.path().extension() == ".yml") {
      YAML::Node config = YAML::LoadFile(entry.path());
      loadVillain(config);
    }
}

void Client::loadVillain(const YAML::Node &node) {
  auto v = std::make_unique<Villain>(node);
  utils::log("LOG", "Loaded villain ", v->name);
  _villains.add(v);
}

bool Client::updateFrame() {
  switch (_state) {

  case State::choose_villain:
    for (auto &p : _players)
      if (!_controls.count(p.name)) {
        p.chooseVillain(_villains, _controls);
        return true;
      }
    _state = State::pre_turn;
    utils::log("GAME STATE", "PRE TURN");
    utils::sendPacket(_server, "Villain picked.");
    enet_host_flush(_client);
    return true;

  case State::pre_turn:
    utils::sendPacket(_server, "Pre turn.");
    enet_host_flush(_client);
    return true;
  }

  throw std::invalid_argument("unknown state.");
}

#pragma once

#include "game/Game.h"
#include "object/Player.h"
#include "object/Villain.h"
#include "utils/UniqueVector.h"
#include "utils/network.h"
#include "yaml.h"
#include <SFML/Window.hpp>
#include <enet/enet.h>
#include <filesystem>
#include <future>
#include <unordered_map>

class Client : public Game {
public:
  enum class State {
    // pre-game
    choose_villain,
    // in-game,
    pre_turn
  };

  Client();
  ~Client();

  void connectToServer();

  void loadPlayer(const std::filesystem::path &path);

  void removePlayer(const std::string &name);

  void removeVillain(const std::string &name);

  void loadExtensions(const std::filesystem::path &path);

  void loadExtension(const std::filesystem::path &path);

  void loadVillains(const std::filesystem::path &path);

  void loadVillain(const YAML::Node &node);

  virtual bool updateFrame() override;

private:
  State _state;
  sf::Window _window;
  std::future<std::string> _get_command;
  UniqueVector<Player> _players;
  UniqueVector<Villain> _villains;
  std::unordered_map<std::string, std::unique_ptr<Villain>> _controls;
  ENetHost *_client;
  ENetPeer *_server;
};
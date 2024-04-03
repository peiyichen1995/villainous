#pragma once

#include "object/Player.h"
#include "object/Villain.h"
#include "utils/IO.h"
#include "utils/UniqueVector.h"
#include "utils/network.h"
#include "yaml.h"
#include <enet/enet.h>
#include <filesystem>
#include <unordered_map>

class Client {
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

  bool updateFrame();

private:
  UniqueVector<Player> _players;
  UniqueVector<Villain> _villains;
  std::unordered_map<std::string, std::unique_ptr<Villain>> _controls;
  State _state;
  ENetHost *_client;
  ENetPeer *_server;
};
#include "game/Client.h"
#include "game/Server.h"
#include "object/Player.h"
#include "object/Villain.h"
#include "utils/config.h"
#include <chrono>
#include <filesystem>
#include <iostream>
#include <memory>

using namespace std::chrono_literals;

// we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
constexpr std::chrono::nanoseconds timestep(16ms);

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  using clock = std::chrono::high_resolution_clock;

  if (enet_initialize() != 0) {
    std::cerr << "An error occurred while initializing ENet." << std::endl;
    return EXIT_FAILURE;
  }
  atexit(enet_deinitialize);

  if (argv[1] == std::string("--serve")) {
    Server s;
    std::chrono::nanoseconds lag(0ns);
    auto time_start = clock::now();

    while (true) {
      auto delta_time = std::chrono::duration_cast<std::chrono::nanoseconds>(
          clock::now() - time_start);

      if (delta_time > timestep) {
        try {
          s.updateFrame();
        } catch (const std::exception &e) {
          utils::log("ERROR", e.what());
        }
        time_start = clock::now();
      }
    }
  } else {
    Client c;
    c.connectToServer();
    c.loadPlayer(fs::path(argv[1]));
    c.loadExtensions(fs::path(argv[0]).parent_path() / VILLAINOUS_EXTENSION);

    std::chrono::nanoseconds lag(0ns);
    auto time_start = clock::now();

    bool keep_going = true;
    while (keep_going) {
      auto delta_time = std::chrono::duration_cast<std::chrono::nanoseconds>(
          clock::now() - time_start);

      if (delta_time > timestep) {
        try {
          keep_going = c.updateFrame();
        } catch (const std::exception &e) {
          utils::log("ERROR", e.what());
        }
        time_start = clock::now();
      }
    }
  }

  return 0;
}
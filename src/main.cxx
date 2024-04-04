#include "game/Client.h"
#include "game/Server.h"
#include "utils/config.h"

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  if (enet_initialize() != 0) {
    std::cerr << "An error occurred while initializing ENet." << std::endl;
    return EXIT_FAILURE;
  }
  atexit(enet_deinitialize);

  if (argv[1] == std::string("--serve")) {
    Server s;
    s.start();
  } else {
    Client c;
    c.loadPlayer(fs::path(argv[1]));
    c.loadExtensions(fs::path(argv[0]).parent_path() / VILLAINOUS_EXTENSION);
    c.connectToServer();
    c.start();
  }

  return 0;
}
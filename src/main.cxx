#include "game/Game.h"
#include "object/Player.h"
#include "object/Villain.h"
#include "utils/config.h"
#include <filesystem>
#include <iostream>
#include <memory>

int main(int argc, char *argv[]) {
  Game g;

  const std::filesystem::path exe(argv[0]);
  g.loadExtensions(exe.parent_path() / VILLAINOUS_EXTENSION);

  g.addPlayer("PangChen");
  g.addPlayer("PangHu");
  g.addPlayer("Rudy");
  g.removePlayer("Rudy");

  while (true) {
    try {
      g.launch();
    } catch (const std::exception &e) {
      utils::log("ERROR", e.what());
    }
  }

  return 0;
}
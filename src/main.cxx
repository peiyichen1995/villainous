#include "game/Game.h"
#include "object/Player.h"
#include "object/Villain.h"
#include <iostream>
#include <memory>

int main() {

  Game g;

  g.addPlayer("PangChen");
  g.addPlayer("PangHu");
  g.addPlayer("Rudy");
  g.removePlayer("Rudy");

  g.addVillain("Jafar");
  g.addVillain("Ursula");
  g.addVillain("BigFat");
  g.removeVillain("BigFat");

  while (true) {
    try {
      g.launch();
    } catch (const std::exception &e) {
      utils::log("ERROR", e.what());
    }
  }

  return 0;
}
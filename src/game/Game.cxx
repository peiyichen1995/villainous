#include "game/Game.h"

void Game::start() {
  using namespace std::chrono_literals;
  using clock = std::chrono::high_resolution_clock;

  constexpr std::chrono::nanoseconds timestep(16ms);

  std::chrono::nanoseconds lag(0ns);
  auto time_start = clock::now();

  bool keep_going = true;
  while (keep_going) {
    auto delta_time = std::chrono::duration_cast<std::chrono::nanoseconds>(
        clock::now() - time_start);

    if (delta_time > timestep) {
      try {
        keep_going = updateFrame();
      } catch (const std::exception &e) {
        utils::log("ERROR", e.what());
      }
      time_start = clock::now();
    }
  }
}
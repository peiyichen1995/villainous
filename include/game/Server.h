#include "game/Game.h"
#include <enet/enet.h>

class Server : public Game {
public:
  Server();
  ~Server();

  virtual bool updateFrame() override;

private:
  ENetHost *_server;
};
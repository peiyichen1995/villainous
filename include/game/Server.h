#include <enet/enet.h>

class Server {
public:
  Server();
  ~Server();

  void updateFrame();

private:
  ENetHost *_server;
};
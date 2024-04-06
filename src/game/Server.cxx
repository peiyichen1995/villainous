#include "game/Server.h"
#include "utils/network.h"

Server::Server() : Game() {
  /* Bind the server to the default localhost.     */
  ENetAddress address;
  address.host = ENET_HOST_ANY;
  address.port = 8000;

  _server = enet_host_create(&address, 2, 1, 0, 0);
  if (!_server) {
    std::cerr << "An error occurred while trying to create an ENet server host."
              << std::endl;
    exit(EXIT_FAILURE);
  }

  utils::log("LOG", "Server created.");
}

Server::~Server() { enet_host_destroy(_server); }

bool Server::updateFrame() {
  ENetEvent event;
  while (enet_host_service(_server, &event, 0)) {
    switch (event.type) {
    case ENET_EVENT_TYPE_CONNECT:
      utils::log("LOG", "A new client conencted from ",
                 event.peer->address.host, ":", event.peer->address.port);
      break;
    case ENET_EVENT_TYPE_RECEIVE:
      utils::log("LOG",
                 std::string(reinterpret_cast<char *>(event.packet->data)));
      /* Clean up the packet now that we're done using it. */
      enet_packet_destroy(event.packet);

      break;

    case ENET_EVENT_TYPE_DISCONNECT:
      throw std::runtime_error("Client disconnected");

    default:;
    }
  }

  if (_server->peerCount == _server->connectedPeers) {
    utils::broadcastPacket(_server, "All players have joined.");
    enet_host_flush(_server);
  }

  return true;
}

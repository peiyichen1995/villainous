#include "utils/network.h"

namespace utils {
void sendPacket(ENetPeer *peer, const std::string &message) {
  ENetPacket *packet = enet_packet_create(message.c_str(), message.length(),
                                          ENET_PACKET_FLAG_RELIABLE);

  enet_peer_send(peer, 0, packet);
}
} // namespace utils
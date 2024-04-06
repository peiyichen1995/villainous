#include <enet/enet.h>
#include <string>

namespace utils {
void sendPacket(ENetPeer *peer, const std::string &message);
void broadcastPacket(ENetHost *host, const std::string &message);
} // namespace utils
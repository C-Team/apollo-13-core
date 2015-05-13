#ifndef APOLLO_REMOTE_PACKET_MANAGER_H_
#define APOLLO_REMOTE_PACKET_MANAGER_H_

#include <string>
#include "apollo/remote/network_packet.h"

namespace apollo {
namespace remote {

class PacketManager {
 public:
  PacketManager(const std::string& address, int port);
  bool Init();
  ~PacketManager();

  bool ReadPacket(CommandPacket* packet);

 private:
  static const int kQueueSize = 1;
  const std::string& address_;
  int port_;
  int sock_;
  int fd_;
};

} // namespace remote
} // namespace apollo

#endif // APOLLO_REMOTE_PACKET_MANAGER_H_

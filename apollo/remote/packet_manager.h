#ifndef APOLLO_REMOTE_PACKET_MANAGER_H_
#define APOLLO_REMOTE_PACKET_MANAGER_H_

#include <string>
#include <netinet/in.h>
#include "apollo/remote/network_packet.h"

namespace apollo {
namespace remote {

class PacketManager {
 public:
  PacketManager(int port);
  bool Init();
  ~PacketManager();

  bool Connect();

  bool IsConnectionValid();

  bool ReadPacket(CommandPacket* packet);

 private:
  static const int kQueueSize = 1;
  sockaddr_in address_struct_;
  int port_;
  int sock_;
  int fd_ = -1;
};

} // namespace remote
} // namespace apollo

#endif // APOLLO_REMOTE_PACKET_MANAGER_H_

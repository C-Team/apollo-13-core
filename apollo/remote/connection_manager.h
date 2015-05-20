#ifndef APOLLO_REMOTE_CONNECTION_MANAGER_H_
#define APOLLO_REMOTE_CONNECTION_MANAGER_H_

#include <string>
#include <functional>
#include "apollo/remote/network_packet.h"
#include "apollo/remote/packet_manager.h"

namespace apollo {
namespace remote {

class ConnectionManager {
 public:
  ConnectionManager(int port);

  bool Start();

  void set_on_start(std::function<bool()> on_start) { on_start_ = on_start; }

  void set_on_failure(std::function<bool()> on_failure) { on_failure_ = on_failure; }

  void set_on_end(std::function<bool()> on_end) { on_end_ = on_end; }

  void set_handler(std::function<bool(CommandPacket*)> handler) { handler_ = handler; }

 private:
  std::function<bool()> on_start_;
  std::function<bool()> on_failure_;
  std::function<bool()> on_end_;
  std::function<bool(CommandPacket*)> handler_;
  PacketManager packet_manager_;
};

} // namespace remote
} // namespace apollo

#endif // APOLLO_REMOTE_CONNECTION_MANAGER_H_

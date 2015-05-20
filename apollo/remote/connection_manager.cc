#include "apollo/remote/connection_manager.h"

namespace apollo {
namespace remote {

ConnectionManager::ConnectionManager(int port) 
    : packet_manager_(port) {}

bool ConnectionManager::Start() {
  if (!packet_manager_.Init()) {
    return false;
  }

  CommandPacket packet;
  while (true) {
    if (!packet_manager_.Connect() || !on_start_()) {
      on_end_();
      return false;
    }

    while (true) {
      if (!packet_manager_.ReadPacket(&packet) && !packet_manager_.IsConnectionValid()) {
        if (!on_failure_()) {
          on_end_();
          return false;
        }
        break;
      }
      handler_(&packet);
    }
  }
  on_end_();
  return false;
}

} // namespace remote
} // namespace apollo

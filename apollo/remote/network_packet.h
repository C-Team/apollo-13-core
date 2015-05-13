#ifndef APOLLO_REMOTE_NETWORK_PACKET_H_
#define APOLLO_REMOTE_NETWORK_PACKET_H_

#include <cstdint>

namespace apollo {
namespace remote {

enum class Command {
  DRIVE_FORWARD = 0,
  DRIVE_BACKWARD = 1,
  TURN_LEFT = 2,
  TURN_RIGHT = 3,
};

struct CommandPacket {
  uint8_t command;
  uint8_t data_0;
  uint8_t data_1;
};

} // namespace remote
} // namespace apollo

#endif // APOLLO_REMOTE_NETWORK_PACKET_H_

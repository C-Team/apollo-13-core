#ifndef APOLLO_REMOTE_NETWORK_PACKET_H_
#define APOLLO_REMOTE_NETWORK_PACKET_H_

#include <cstdint>

namespace apollo {
namespace remote {

struct CommandPacket {
  uint8_t command;
  uint8_t data_0;
  uint8_t data_1;
};

enum class Command {
  SET_SPEED = 0,
  SET_DIRECTION = 1,
  SET_DIGGER_WHEEL_SPEED = 2,
  SET_DIGGER_VERTICAL_SPEED = 3,
  SET_DIGGER_VERTICAL_POSITION = 4,
  SET_CONVEYOR_1_SPEED = 5,
  SET_CONVEYOR_2_SPEED = 6,
  SET_CONVEYOR_1_STATUS = 7,
  SET_CONVEYOR_2_STATUS = 8,
};

} // namespace remote
} // namespace apollo

#endif // APOLLO_REMOTE_NETWORK_PACKET_H_

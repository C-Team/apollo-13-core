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

class Command {
 public:
  enum CommandType {
    DRIVE_FORWARD = 0,
    DRIVE_BACKWARD = 1,
    TURN_LEFT = 2,
    TURN_RIGHT = 3,
  };

  virtual CommandType type() = 0;
};

class DriveCommand : public Command {
 public:
  DriveCommand(uint8_t speed, CommandType type) : speed_(speed), type_(type) {}

  CommandType type() { return type_; }

  uint8_t speed() { return speed_; };

 private:
  uint8_t speed_;
  CommandType type_;
};

class DriveForward : public DriveCommand {
 public:
  DriveForward(uint8_t speed) : DriveCommand(speed, DRIVE_FORWARD) {}
};

class DriveBackward : public DriveCommand {
 public:
  DriveBackward(uint8_t speed) : DriveCommand(speed, DRIVE_FORWARD) {}
};

class TurnLeft : public DriveCommand {
 public:
  TurnLeft(uint8_t speed) : DriveCommand(speed, DRIVE_FORWARD) {}
};

class TurnRight : public DriveCommand {
 public:
  TurnRight(uint8_t speed) : DriveCommand(speed, DRIVE_FORWARD) {}
};

} // namespace remote
} // namespace apollo

#endif // APOLLO_REMOTE_NETWORK_PACKET_H_

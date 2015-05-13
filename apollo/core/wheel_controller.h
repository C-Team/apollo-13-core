#ifndef APOLLO_CORE_WHEEL_CONTROLLER_H_
#define APOLLO_CORE_WHEEL_CONTROLLER_H_

#include <cstdint>
#include <string>
#include "apollo/core/motor_controller.h"

namespace apollo {
namespace core {

class WheelController {
 public:
  WheelController();

  bool Init();

  bool DriveForward(uint8_t speed);

  bool DriveBackward(uint8_t speed);

  bool TurnLeft(uint8_t speed);

  bool TurnRight(uint8_t speed);

 private:
  static const std::string serial_tty_path_0_;
  static const std::string serial_tty_path_1_;
  static const uint8_t controller_address_0_;
  static const uint8_t controller_address_1_;

  MotorController motor_controller_0_;
  MotorController motor_controller_1_;
};

} // namespace core
} // namespace apollo

#endif // APOLLO_CORE_WHEEL_CONTROLLER_H_

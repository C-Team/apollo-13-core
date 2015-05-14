#ifndef APOLLO_CORE_DIGGER_CONTROLLER_H_
#define APOLLO_CORE_DIGGER_CONTROLLER_H_

#include <cstdint>
#include <string>
#include "apollo/core/motor_controller.h"

namespace apollo {
namespace core {

class DiggerController {
 public:
  DiggerController();

  bool SetWheelSpeed(int8_t speed);

  bool SetVerticalSpeed(int8_t speed);

 private:
  static const std::string serial_tty_path_wheel_motor_;
  static const std::string serial_tty_path_vertical_motor_;
  static const uint8_t controller_address_wheel_motor_;
  static const uint8_t controller_address_vertical_motor_;

  MotorController motor_controller_wheel_motor_;
  MotorController motor_controller_vertical_motor_;
};

} // namespace core
} // namespace apollo

#endif // APOLLO_CORE_DIGGER_CONTROLLER_H_

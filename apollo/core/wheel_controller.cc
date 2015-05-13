#include "apollo/core/wheel_controller.h"

namespace apollo {
namespace core {

WheelController::WheelController() : 
    motor_controller_0_(serial_tty_path_0_, controller_address_0_), 
    motor_controller_1_(serial_tty_path_1_, controller_address_1_) {}

bool WheelController::Init() {
  return motor_controller_0_.Init() && motor_controller_1_.Init();
}

bool WheelController::DriveForward(uint8_t speed) {
  return motor_controller_0_.DriveForwardMixed(speed) && 
      motor_controller_1_.DriveForwardMixed(speed);
}

bool WheelController::DriveBackward(uint8_t speed) {
  return motor_controller_0_.DriveBackwardMixed(speed) &&
      motor_controller_1_.DriveBackwardMixed(speed);
}

bool WheelController::TurnLeft(uint8_t speed) {
  return motor_controller_0_.TurnLeftMixed(speed) &&
      motor_controller_1_.TurnLeftMixed(speed);
}

bool WheelController::TurnRight(uint8_t speed) {
  return motor_controller_0_.TurnRightMixed(speed) &&
      motor_controller_1_.TurnRightMixed(speed);
}

} // namespace core
} // namespace apollo

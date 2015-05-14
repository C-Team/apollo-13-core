#include "apollo/core/wheel_controller.h"

namespace apollo {
namespace core {

WheelController::WheelController() : 
    motor_controller_0_(serial_tty_path_0_, controller_address_0_), 
    motor_controller_1_(serial_tty_path_1_, controller_address_1_) {}

bool WheelController::Init() {
  return motor_controller_0_.Init() && motor_controller_1_.Init();
}

bool WheelController::SetSpeed(int8_t speed) {
  return motor_controller_0_.SetSpeed(speed) &&
      motor_controller_1_.SetSpeed(speed);
}

bool WheelController::SetDirection(int8_t speed) {
  return motor_controller_0_.SetDirection(speed) &&
      motor_controller_1_.SetDirection(speed);
}

} // namespace core
} // namespace apollo

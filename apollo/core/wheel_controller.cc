#include "apollo/core/wheel_controller.h"

#include "apollo/core/motor_definitions.h"

namespace apollo {
namespace core {

WheelController::WheelController() : 
    motor_controller_wheel_motor_0_(serial_tty_path_wheel_motor_0_,
                                    controller_address_wheel_motor_0_), 
    motor_controller_wheel_motor_1_(serial_tty_path_wheel_motor_1_, 
                                    controller_address_wheel_motor_1_) {}

bool WheelController::Init() {
  return motor_controller_wheel_motor_0_.Init() && 
      motor_controller_wheel_motor_1_.Init();
}

bool WheelController::SetSpeed(int8_t speed) {
  return motor_controller_wheel_motor_0_.SetSpeed(speed) &&
      motor_controller_wheel_motor_1_.SetSpeed(speed);
}

bool WheelController::SetDirection(int8_t speed) {
  return motor_controller_wheel_motor_0_.SetDirection(speed) &&
      motor_controller_wheel_motor_1_.SetDirection(speed);
}

} // namespace core
} // namespace apollo

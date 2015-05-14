#include "apollo/core/digger_controller.h"
namespace apollo {
namespace core {

DiggerController::DiggerController() :
    motor_controller_wheel_motor_(serial_tty_path_wheel_motor_, 
                                  controller_address_wheel_motor_),
    motor_controller_vertical_motor_(serial_tty_path_vertical_motor_, 
                                     controller_address_vertical_motor_) {}

bool DiggerController::SetWheelSpeed(int8_t speed) {
  return motor_controller_wheel_motor_.SetSpeed(speed);
}

bool DiggerController::SetVerticalSpeed(int8_t speed) {
  return motor_controller_vertical_motor_.SetSpeed(speed);
}

} // namespace core
} // namespace apollo

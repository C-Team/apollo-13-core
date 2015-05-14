#include "apollo/core/digger_controller.h"

#include "apollo/core/motor_definitions.h"

namespace apollo {
namespace core {

DiggerController::DiggerController() :
    motor_controller_digger_motor_(serial_tty_path_digger_motor_, 
                                  controller_address_digger_motor_),
    motor_controller_vertical_motor_(serial_tty_path_vertical_motor_, 
                                     controller_address_vertical_motor_) {}

bool DiggerController::SetWheelSpeed(int8_t speed) {
  return motor_controller_digger_motor_.SetSpeed(speed);
}

bool DiggerController::SetVerticalSpeed(int8_t speed) {
  return motor_controller_vertical_motor_.SetSpeed(speed);
}

} // namespace core
} // namespace apollo

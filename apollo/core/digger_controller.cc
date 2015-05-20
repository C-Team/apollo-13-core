#include "apollo/core/digger_controller.h"

#include <unistd.h>
#include "apollo/core/motor_definitions.h"

namespace apollo {
namespace core {

DiggerController::DiggerController() :
    motor_controller_digger_motor_(kSerialTTYPathDiggerMotor, 
                                   kControllerAddressDiggerMotor),
    position_controller_(
        &vertical_feedback_, 
        [this](uint8_t speed) { return this->SetVerticalSpeedInternal(speed); }) {}

bool DiggerController::Init() {
  return motor_controller_digger_motor_.Init() 
      && vertical_feedback_.Init()
      && position_controller_.Init();
}

bool DiggerController::SetWheelSpeed(int8_t speed) {
  return SetWheelSpeedInternal(speed);
}

bool DiggerController::SetVerticalSpeed(int8_t speed) {
  position_controller_.SetIgnore();
  return SetVerticalSpeedInternal(speed);
}

bool DiggerController::SetVerticalPosition(uint8_t position) {
  return position_controller_.SetVerticalPosition(position);
}

int DiggerController::ReadCurrentValue() {
  return position_controller_.ReadCurrentValue();
}

bool DiggerController::SetWheelSpeedInternal(int8_t speed) {
  return motor_controller_digger_motor_.SetSpeedMotor2(speed);
}

bool DiggerController::SetVerticalSpeedInternal(int8_t speed) {
  return motor_controller_digger_motor_.SetSpeedMotor1(speed);
}

} // namespace core
} // namespace apollo

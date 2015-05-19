#include "apollo/core/conveyor_controller.h"

#include "apollo/core/motor_definitions.h"

namespace apollo {
namespace core {
namespace {
static const int8_t kConveyorSpeed1 = 20;
static const int8_t kConveyorSpeed2 = 20;
} // namespace

ConveyorController::ConveyorController() : motor_controller_(
    kSerialTTYPathConveyorMotor, kControllerAddressConveyorMotor) {}

bool ConveyorController::Init() {
  return motor_controller_.Init();
}

bool ConveyorController::SetSpeedConveyor1(int8_t speed) {
  return motor_controller_.SetSpeedMotor1(speed);
}

bool ConveyorController::TurnOnConveyor1() {
  return SetSpeedConveyor1(kConveyorSpeed1);
}

bool ConveyorController::TurnOffConveyor1() {
  return SetSpeedConveyor1(0);
}

bool ConveyorController::SetSpeedConveyor2(int8_t speed) {
  return motor_controller_.SetSpeedMotor2(speed);
}

bool ConveyorController::TurnOnConveyor2() {
  return SetSpeedConveyor2(kConveyorSpeed1);
}

bool ConveyorController::TurnOffConveyor2() {
  return SetSpeedConveyor2(0);
}

} // namespace core
} // namespace apollo

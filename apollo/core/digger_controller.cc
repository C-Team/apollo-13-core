#include "apollo/core/digger_controller.h"

#include <unistd.h>
#include "apollo/core/motor_definitions.h"

namespace apollo {
namespace core {

DiggerController::DiggerController() : 
    motor_controller_digger_motor_(kSerialTTYPathDiggerMotor, 
                                   kControllerAddressDiggerMotor) {}

bool DiggerController::Init() {
  return motor_controller_digger_motor_.Init();
}

bool DiggerController::SetSpeed(int8_t speed) {
  printf("About to set speed to %d\n", speed);
  return motor_controller_digger_motor_.SetSpeed(speed);
}

bool DiggerController::SetDirection(int8_t speed) {
  return motor_controller_digger_motor_.SetDirection(speed);
}

// bool DiggerController::SetWheelSpeedInternal(int8_t speed) {
//   printf("Setting wheel speed to: %d\n", speed);
//   return motor_controller_digger_motor_.SetSpeed(speed);
// }
// 
// bool DiggerController::SetVerticalSpeedInternal(int8_t speed) {
//   printf("Setting vertical speed to: %d\n", speed);
//   return motor_controller_digger_motor_.SetSpeed(speed);
// }

} // namespace core
} // namespace apollo

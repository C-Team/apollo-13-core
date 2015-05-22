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

  bool SetSpeed(int8_t speed);

  bool SetDirection(int8_t speed);

 private:
  MotorController motor_controller_wheel_motor_0_;
  MotorController motor_controller_wheel_motor_1_;
};

} // namespace core
} // namespace apollo

#endif // APOLLO_CORE_WHEEL_CONTROLLER_H_

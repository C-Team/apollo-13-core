#ifndef APOLLO_CORE_CONVEYOR_CONTROLLER_H_
#define APOLLO_CORE_CONVEYOR_CONTROLLER_H_

#include <cstdint>
#include "apollo/core/motor_controller.h"

namespace apollo {
namespace core {

class ConveyorController {
 public:
  ConveyorController();

  bool Init();

  // LARGE_CONVEYOR
  bool SetSpeedConveyor1(int8_t speed);

  bool TurnOnConveyor1();

  bool TurnOffConveyor1();

  // SMALL_CONVEYOR
  bool SetSpeedConveyor2(int8_t speed);

  bool TurnOnConveyor2();

  bool TurnOffConveyor2();

 private:
  MotorController motor_controller_;
};

} // namespace core
} // namespace apollo

#endif // APOLLO_CORE_CONVEYOR_CONTROLLER_H_

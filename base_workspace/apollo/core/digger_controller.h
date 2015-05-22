#ifndef APOLLO_CORE_DIGGER_CONTROLLER_H_
#define APOLLO_CORE_DIGGER_CONTROLLER_H_

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <mutex>
#include <string>
#include <thread>
#include "apollo/core/feedback_potentiometer.h"
#include "apollo/core/motor_controller.h"
#include "apollo/core/position_controller.h"

namespace apollo {
namespace core {

class DiggerController {
 public:
  DiggerController();

  bool Init();

  bool SetWheelSpeed(int8_t speed);

  bool SetVerticalSpeed(int8_t speed);

  bool SetVerticalPosition(uint8_t position);

  int ReadCurrentValue();

 private:
  FeedbackPotentiometer vertical_feedback_;
  MotorController motor_controller_digger_motor_;
  PositionController position_controller_;
  
  bool SetWheelSpeedInternal(int8_t speed);
  bool SetVerticalSpeedInternal(int8_t speed);
};

} // namespace core
} // namespace apollo

#endif // APOLLO_CORE_DIGGER_CONTROLLER_H_

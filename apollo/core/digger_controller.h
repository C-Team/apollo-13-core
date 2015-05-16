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

namespace apollo {
namespace core {

class DiggerController {
 public:
  DiggerController();
  bool Init();
  ~DiggerController();

  bool SetWheelSpeed(int8_t speed);

  bool SetVerticalPosition(uint8_t position);

 private:
  FeedbackPotentiometer vertical_feedback_;
  MotorController motor_controller_digger_motor_;
  
  std::thread position_thread_;
  std::atomic<bool> is_running_;
  uint8_t desired_position_ = 0;
  std::condition_variable_any cv_;
  std::mutex lock_;

  bool SetWheelSpeedInternal(int8_t speed);
  bool SetVerticalSpeedInternal(int8_t speed);

  void ControlLoop();

  void LowerToPosition(uint8_t position);
  void RaiseToPosition(uint8_t position);
};

} // namespace core
} // namespace apollo

#endif // APOLLO_CORE_DIGGER_CONTROLLER_H_

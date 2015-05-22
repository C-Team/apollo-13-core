#ifndef APOLLO_CORE_POSITION_CONTROLLER_H_
#define APOLLO_CORE_POSITION_CONTROLLER_H_

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <functional>
#include <mutex>
#include <thread>
#include "apollo/core/feedback_potentiometer.h"

namespace apollo {
namespace core {

class PositionController {
 public:
  PositionController(FeedbackPotentiometer* vertical_feedback,
                     std::function<bool(int8_t)> position_setter);

  bool Init();

  ~PositionController();

  int ReadCurrentValue();

  bool SetVerticalPosition(uint8_t position);

  void SetIgnore();

 private:
  FeedbackPotentiometer* vertical_feedback_;
  std::function<bool(int8_t)> position_setter_;
  std::atomic<bool> is_ignored_;
  std::thread position_thread_;
  std::atomic<bool> is_running_;
  uint8_t desired_position_ = 0;
  std::condition_variable_any cv_;
  std::mutex lock_;

  void ControlLoop();

  void LowerToPosition(uint8_t position);
  void RaiseToPosition(uint8_t position);
  uint8_t GetCurrentPosition();
};

} // namespace core
} // namespace apollo

#endif // APOLLO_CORE_POSITION_CONTROLLER_H_

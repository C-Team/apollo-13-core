#include "apollo/core/digger_controller.h"

#include <unistd.h>
#include "apollo/core/motor_definitions.h"

namespace apollo {
namespace core {

using std::unique_lock;

DiggerController::DiggerController() :
    motor_controller_digger_motor_(serial_tty_path_digger_motor_, 
                                  controller_address_digger_motor_), 
    is_running_(true) {}

bool DiggerController::Init() {
  position_thread_ = std::thread([this]{ this->ControlLoop(); });
  return motor_controller_digger_motor_.Init();
}

DiggerController::~DiggerController() {
  is_running_ = false;
  position_thread_.join();
}

bool DiggerController::SetWheelSpeed(int8_t speed) {
  return SetWheelSpeedInternal(speed);
}

bool DiggerController::SetVerticalPosition(uint8_t position) {
  lock_.lock();
  desired_position_ = position;
  cv_.notify_all();
  lock_.unlock();
  return false;
}

void DiggerController::ControlLoop() {
  while (true) {
    lock_.lock();
    cv_.wait(lock_);
    lock_.unlock();
    int current_desired = desired_position_;
    if (current_desired > vertical_feedback_.ReadCurrentValue()) {
      LowerToPosition(current_desired);
    } else if (current_desired < vertical_feedback_.ReadCurrentValue()) {
      RaiseToPosition(current_desired);
    }
  }
}

void DiggerController::LowerToPosition(uint8_t position) {
  SetVerticalSpeedInternal(-64);
  while (position > vertical_feedback_.ReadCurrentValue()) {
    sleep(1);
  }
  SetVerticalSpeedInternal(0);
}

void DiggerController::RaiseToPosition(uint8_t position) {
  SetVerticalSpeedInternal(63);
  while (position < vertical_feedback_.ReadCurrentValue()) {
    sleep(1);
  }
  SetVerticalSpeedInternal(0);
}

} // namespace core
} // namespace apollo

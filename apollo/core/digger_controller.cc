#include "apollo/core/digger_controller.h"

#include <unistd.h>
#include "apollo/core/motor_definitions.h"

namespace apollo {
namespace core {
namespace {
static const uint8_t kMinPosition = 0;
static const uint8_t kMaxPosition = 16;
static const int8_t kRaiseSpeed = 63;
static const int8_t kLowerSpeed = -64;
} // namespace

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
  if (position > kMaxPosition) {
    position = kMaxPosition;
  }

  lock_.lock();
  desired_position_ = position;
  cv_.notify_all();
  lock_.unlock();
  return true;
}

uint8_t DiggerController::GetCurrentPosition() {
  return vertical_feedback_.ReadCurrentValue() / 100;
}

void DiggerController::ControlLoop() {
  while (true) {
    lock_.lock();
    cv_.wait(lock_);
    lock_.unlock();
    int current_desired = desired_position_;
    if (current_desired > GetCurrentPosition()) {
      LowerToPosition(current_desired);
    } else if (current_desired < GetCurrentPosition()) {
      RaiseToPosition(current_desired);
    }
  }
}

void DiggerController::LowerToPosition(uint8_t position) {
  SetVerticalSpeedInternal(kLowerSpeed);
  while (position > GetCurrentPosition()) {
    sleep(1);
  }
  SetVerticalSpeedInternal(0);
}

void DiggerController::RaiseToPosition(uint8_t position) {
  SetVerticalSpeedInternal(kRaiseSpeed);
  while (position < GetCurrentPosition()) {
    sleep(1);
  }
  SetVerticalSpeedInternal(0);
}

} // namespace core
} // namespace apollo

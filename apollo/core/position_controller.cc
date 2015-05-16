#include "apollo/core/position_controller.h"

#include <unistd.h>

namespace apollo {
namespace core {
namespace {
static const uint8_t kMinPosition = 0;
static const uint8_t kMaxPosition = 16;
static const int8_t kRaiseSpeed = 63;
static const int8_t kLowerSpeed = -64;
static const int kSleepTime = 1;
} // namespace

PositionController::PositionController(FeedbackPotentiometer* vertical_feedback,
                                       std::function<bool(int8_t)> position_setter) :
    vertical_feedback_(vertical_feedback), 
    position_setter_(position_setter),
    is_ignored_(true),
    is_running_(true) {}

bool PositionController::Init() {
  position_thread_ = std::thread([this]{ this->ControlLoop(); });
  return true;
}

PositionController::~PositionController() {
  is_running_ = false;
  position_thread_.join();
}

bool PositionController::SetVerticalPosition(uint8_t position) {
  if (position > kMaxPosition) {
    position = kMaxPosition;
  }

  is_ignored_ = false;
  lock_.lock();
  desired_position_ = position;
  cv_.notify_all();
  lock_.unlock();
  return true;
}

void PositionController::SetIgnore() {
  is_ignored_ = true;
}

uint8_t PositionController::GetCurrentPosition() {
  return vertical_feedback_->ReadCurrentValue() / 100;
}

void PositionController::ControlLoop() {
  while (true) {
    lock_.lock();
    cv_.wait(lock_);
    lock_.unlock();

    if (is_ignored_) {
      continue;
    }

    int current_desired = desired_position_;
    if (current_desired > GetCurrentPosition()) {
      printf("LowerToPosition = %d\n", current_desired);
      LowerToPosition(current_desired);
    } else if (current_desired < GetCurrentPosition()) {
      printf("RaiseToPosition = %d\n", current_desired);
      RaiseToPosition(current_desired);
    }
  }
}

void PositionController::LowerToPosition(uint8_t position) {
  printf("LowerToPosition, setting speed\n");
  position_setter_(kLowerSpeed);
  while (position > GetCurrentPosition()) {
    if (is_ignored_) {
      return;
    }
    sleep(kSleepTime);
  }
  if (is_ignored_) {
    return;
  }
  position_setter_(0);
}

void PositionController::RaiseToPosition(uint8_t position) {
  printf("RaiseToPosition, setting speed\n");
  position_setter_(kRaiseSpeed);
  while (position < GetCurrentPosition()) {
    if (is_ignored_) {
      return;
    }
    sleep(kSleepTime);
  }
  if (is_ignored_) {
    return;
  }
  position_setter_(0);
}

} // namespace core
} // namespace apollo

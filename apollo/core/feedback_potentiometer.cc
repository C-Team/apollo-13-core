#include "apollo/core/feedback_potentiometer.h"

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "apollo/core/motor_definitions.h"

namespace apollo {
namespace core {

using std::string;

static const int kMinValue = 0;
static const int kMaxValue = 16;

bool FeedbackPotentiometer::Init() {
  fd_ = open(kFeedbackPotentiometerFile.c_str(), O_RDONLY);
  return fd_ >= 0;
}

FeedbackPotentiometer::~FeedbackPotentiometer() {
  close(fd_);
}

int FeedbackPotentiometer::ReadCurrentValue() {
  // TODO: There should be a better way to read this value than opening and
  // closing the file everytime we want to read the value in the file.
  const int buffer_size = 5;
  char buffer[buffer_size];
  int amount_read = read(fd_, &buffer, buffer_size - 1);
  buffer[amount_read] = '\0';
  if (lseek(fd_, 0, SEEK_SET) != 0) {
    return -1;
  }
  return atoi(buffer);
}

} // namespace core
} // namespace apollo

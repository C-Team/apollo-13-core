#ifndef APOLLO_CORE_FEEDBACK_POTENTIOMETER_H_
#define APOLLO_CORE_FEEDBACK_POTENTIOMETER_H_

namespace apollo {
namespace core {

class FeedbackPotentiometer {
 public:
  bool Init();
  ~FeedbackPotentiometer();

  int ReadCurrentValue();

 private:
  int fd_;
};

} // namespace core
} // namespace apollo

#endif // APOLLO_CORE_FEEDBACK_POTENTIOMETER_H_

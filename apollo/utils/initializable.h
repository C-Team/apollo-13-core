#ifndef APOLLO_UTILS_INITIALIZABLE_H_
#define APOLLO_UTILS_INITIALIZABLE_H_

#include "apollo/utils/error.h"

namespace apollo {
namespace utils {

class Initializable {
 public:
  virtual Error Init() __attribute__ ((warn_unused_result)) = 0;
};

} // namespace utils
} // namespace apollo

#endif // APOLLO_UTILS_INITIALIZABLE_H_

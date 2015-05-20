#ifndef APOLLO_UTILS_ERROR_H_
#define APOLLO_UTILS_ERROR_H_

#include <errno.h>
#include <string>

namespace apollo {
namespace utils {

class Error {
 public:
  Error(std::string error_msg) : error_msg_(error_msg) {}
  Error(std::string error_msg, int line_number, std::string file_name) :
      error_msg_(error_msg), line_number_(line_number), file_name_(file_name) {}

  static Error Success() {
    Error success("Success");
    success.is_success_ = true;
    return success;
  }

  Error Because(Error error) {
    return Error(error_msg() + "\nBecause of: " + error.to_string());
  }

  operator bool() const { return is_success(); }

  const std::string& error_msg() const { return error_msg_; }

  virtual bool is_success() const { return is_success_; }

  bool is_error() const { return !is_success(); }

  std::string to_string() {
    if (line_number_ >= 0) {
      return file_name_ + ":" + std::to_string(line_number_) + "] " + error_msg();
    } else {
      return error_msg();
    }
  }

 private:
  std::string error_msg_;
  bool is_success_ = false;
  int line_number_ = -1;
  std::string file_name_ = "";
};

#define ERROR(error_msg) apollo::utils::Error(error_msg, __LINE__, __FILE__)

} // namespace utils
} // namespace apollo

#endif // APOLLO_UTILS_ERROR_H_

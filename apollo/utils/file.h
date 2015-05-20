#ifndef APOLLO_UTILS_FILE_H_
#define APOLLO_UTILS_FILE_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "apollo/utils/error.h"

namespace apollo {
namespace utils {

class FileLike {
 public:
  ~FileLike();
  Error ReadExact(void* buffer, size_t size) __attribute__ ((warn_unused_result));
  Error ReadPartial(void* buffer, size_t size, int* amount_read) __attribute__ ((warn_unused_result));
  Error Write(void* buffer, size_t size) __attribute__ ((warn_unused_result));
  Error Close() __attribute__ ((warn_unused_result));

 protected:
  void Own(int fd);

 private:
  int fd_;
  bool owns_fd_ = false;
};

class File : public FileLike {
 public:
  enum Mode {
    READ_ONLY = O_RDONLY,
    WRITE_ONLY = O_WRONLY,
    READ_AND_WRITE = O_RDWR,
  };

  Error Open(const std::string& file_name, Mode mode) __attribute__ ((warn_unused_result));
};

} // namespace utils
} // namespace apollo

#endif // APOLLO_UTILS_FILE_H_

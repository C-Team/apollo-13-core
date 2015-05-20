#include "apollo/utils/file.h"

#include <unistd.h>

namespace apollo {
namespace utils {

FileLike::~FileLike() {
  if (owns_fd_) {
    Error error = Close();
    if (error) {
      printf("%s\n", error.error_msg().c_str());
    }
  }
}

void FileLike::Own(int fd) {
  owns_fd_ = true;
  fd_ = fd;
}

Error FileLike::ReadExact(void* buffer, size_t size) {
  int amount_read;
  Error error = ReadPartial(buffer, size, &amount_read);
  if (error) {
    return error;
  }
  if (amount_read < static_cast<int>(size)) {
    return ERROR("Amount read did not match size.");
  }
  return Error::Success();
}

Error FileLike::ReadPartial(void* buffer, size_t size, int* amount_read) {
  if (!owns_fd_) {
    return ERROR("Does not own file handle.");
  }

  *amount_read = read(fd_, buffer, size);
  if (*amount_read < 0) {
    return ERROR("Error reading.");
  }
  return Error::Success();
}

Error FileLike::Write(void* buffer, size_t size) {
  if (!owns_fd_) {
    return ERROR("Does not own file handle.");
  }

  int amount_written = write(fd_, buffer, size);
  if (amount_written < 0) {
    return ERROR("Error writing.");
  }
  if (amount_written < static_cast<int>(size)) {
    return ERROR("Amount read did not match size.");
  }
  return Error::Success();
}

Error FileLike::Close() {
  if (!owns_fd_) {
    return ERROR("Does not own file handle.");
  }

  if (close(fd_) < 0) {
    return ERROR("File did not close properly.");
  }
  return Error::Success();
}

Error File::Open(const std::string& file_name, Mode mode) {
  int fd = open(file_name.c_str(), mode);
  if (fd < 0) {
    return ERROR("Failed to open.");
  }
  Own(fd);
  return Error::Success();
}

} // namespace utils
} // namespace apollo

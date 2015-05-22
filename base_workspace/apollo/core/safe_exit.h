#ifndef APOLLO_CORE_SAFE_EXIT_H_
#define APOLLO_CORE_SAFE_EXIT_H_

#include <cstdint>
#include <string>

namespace apollo {
namespace core {

void KillMotor(const std::string& serial_tty_path, uint8_t bus_address);

extern int sockfd;

// Sets up the program for safe termination.
void SetUpSafeExit();

} // namespace core
} // namespace apollo

#endif // APOLLO_CORE_SAFE_EXIT_H_

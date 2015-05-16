#include "apollo/core/safe_exit.h"

#include <csignal>
#include <fcntl.h>
#include <unistd.h>
#include "apollo/core/serial.h"
#include "apollo/core/motor_definitions.h"

namespace apollo {
namespace core {

void SafeExit() {
  KillMotor(kSerialTTYPathWheelMotor0, kControllerAddressWheelMotor0);
  KillMotor(kSerialTTYPathWheelMotor1, kControllerAddressWheelMotor1);
  KillMotor(kSerialTTYPathDiggerMotor, kControllerAddressDiggerMotor);
  KillMotor(kSerialTTYPathConveyorMotor, kControllerAddressConveyorMotor);
}

void KillMotor(const std::string& serial_tty_path, uint8_t bus_address) {
  int fd = open(serial_tty_path.c_str(), O_WRONLY);
  SerialPacket packet;
  SetDirection(&packet, bus_address, 0);
  WritePacket(fd, &packet);
  SetSpeed(&packet, bus_address, 0);
  WritePacket(fd, &packet);
  close(fd);
}

void SignalSafeExit(int) {
  exit(EXIT_FAILURE);
}

void SetUpSafeExit() {
  atexit(*SafeExit);
  signal(SIGABRT, *SignalSafeExit);
  signal(SIGFPE, *SignalSafeExit);
  signal(SIGILL, *SignalSafeExit);
  signal(SIGINT, *SignalSafeExit);
  signal(SIGSEGV, *SignalSafeExit);
  signal(SIGTERM, *SignalSafeExit);
}

} // namespace core
} // namespace apollo

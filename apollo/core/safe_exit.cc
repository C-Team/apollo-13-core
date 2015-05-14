#include "apollo/core/safe_exit.h"

#include <csignal>
#include <fcntl.h>
#include <unistd.h>
#include "apollo/core/serial.h"
#include "apollo/core/motor_definitions.h"

namespace apollo {
namespace core {

void SafeExit() {
  KillMotor(serial_tty_path_wheel_motor_0_, controller_address_wheel_motor_0_);
  KillMotor(serial_tty_path_wheel_motor_1_, controller_address_wheel_motor_1_);
  KillMotor(serial_tty_path_digger_motor_, controller_address_digger_motor_);
  KillMotor(serial_tty_path_vertical_motor_, controller_address_vertical_motor_);
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

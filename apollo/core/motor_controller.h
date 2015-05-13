#ifndef APOLLO_CORE_MOTOR_CONTROLLER_H_
#define APOLLO_CORE_MOTOR_CONTROLLER_H_

#include <cstdint>
#include <string>
#include "apollo/core/serial.h"

namespace apollo {
namespace core {

class MotorController {
 public:
  MotorController(const std::string& serial_tty_path, uint8_t bus_address);

  // Opening the serial channel may fail, do not want to create an invalid
  // object.
  bool Init();

  ~MotorController();

  bool DriveForwardMotor1(uint8_t speed);

  bool DriveBackwardMotor1(uint8_t speed);

  bool MinVoltage(float volts);

  bool MaxVoltage(float volts);

  bool DriveForwardMotor2(uint8_t speed);

  bool DriveBackwardMotor2(uint8_t speed);

  bool DriveForwardMixed(uint8_t speed);

  bool DriveBackwardMixed(uint8_t speed);

  bool TurnRightMixed(uint8_t speed);

  bool TurnLeftMixed(uint8_t speed);

  bool SerialTimeout(unsigned int milliseconds);

  bool SetBaudRate(BaudRate baud_rate);

  bool SetRamping(RampLevel level);

  bool SetDeadband(uint8_t threshold);

 private:
  const std::string& serial_tty_path_;
  uint8_t bus_address_;
  int serial_fd_;
  SerialPacket packet_;
};

} // namespace core
} // namespace apollo

#endif // APOLLO_CORE_MOTOR_CONTROLLER_H_

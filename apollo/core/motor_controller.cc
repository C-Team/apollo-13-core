#include "apollo/core/motor_controller.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

namespace apollo {
namespace core {

MotorController::MotorController(const std::string& serial_tty_path, 
                                 uint8_t bus_address) 
    : serial_tty_path_(serial_tty_path), bus_address_(bus_address) {}

bool MotorController::Init() {
  serial_fd_ = open(serial_tty_path_.c_str(), O_WRONLY);
  BaudRate baud_rate = BaudRate::BR9600;
  SetTTYBaudRate(serial_fd_, baud_rate);
  core::SetBaudRate(&packet_, bus_address_, baud_rate);
  WritePacket(serial_fd_, &packet_);
  return serial_fd_;
}

MotorController::~MotorController() {
  // The TTY and the motor controller remember what baud rate they were set at
  // last; this puts them is a known state.
  SetBaudRate(BaudRate::BR9600);
  close(serial_fd_);
}

bool MotorController::DriveForwardMotor1(uint8_t speed) {
  core::DriveForwardMotor1(&packet_, bus_address_, speed);
  return WritePacket(serial_fd_, &packet_);
}

bool MotorController::DriveBackwardMotor1(uint8_t speed) {
  core::DriveBackwardMotor1(&packet_, bus_address_, speed);
  return WritePacket(serial_fd_, &packet_);
}

bool MotorController::MinVoltage(float volts) {
  core::MinVoltage(&packet_, bus_address_, volts);
  return WritePacket(serial_fd_, &packet_);
}

bool MotorController::MaxVoltage(float volts) {
  core::MaxVoltage(&packet_, bus_address_, volts);
  return WritePacket(serial_fd_, &packet_);
}

bool MotorController::DriveForwardMotor2(uint8_t speed) {
  core::DriveForwardMotor2(&packet_, bus_address_, speed);
  return WritePacket(serial_fd_, &packet_);
}

bool MotorController::DriveBackwardMotor2(uint8_t speed) {
  core::DriveBackwardMotor2(&packet_, bus_address_, speed);
  return WritePacket(serial_fd_, &packet_);
}

bool MotorController::SetSpeedMotor1(uint8_t speed) {
  core::SetSpeedMotor1(&packet_, bus_address_, speed);
  return WritePacket(serial_fd_, &packet_);
}

bool MotorController::SetSpeedMotor2(uint8_t speed) {
  core::SetSpeedMotor2(&packet_, bus_address_, speed);
  return WritePacket(serial_fd_, &packet_);
}

bool MotorController::DriveForwardMixed(uint8_t speed) {
  core::DriveForwardMixed(&packet_, bus_address_, speed);
  return WritePacket(serial_fd_, &packet_);
}

bool MotorController::DriveBackwardMixed(uint8_t speed) {
  core::DriveBackwardMixed(&packet_, bus_address_, speed);
  return WritePacket(serial_fd_, &packet_);
}

bool MotorController::TurnRightMixed(uint8_t speed) {
  core::TurnRightMixed(&packet_, bus_address_, speed);
  return WritePacket(serial_fd_, &packet_);
}

bool MotorController::TurnLeftMixed(uint8_t speed) {
  core::TurnLeftMixed(&packet_, bus_address_, speed);
  return WritePacket(serial_fd_, &packet_);
}

bool MotorController::SetSpeed(int8_t speed) {
  core::SetSpeed(&packet_, bus_address_, speed);
  return WritePacket(serial_fd_, &packet_);
}

bool MotorController::SetDirection(int8_t speed) {
  core::SetDirection(&packet_, bus_address_, speed);
  return WritePacket(serial_fd_, &packet_);
}

bool MotorController::SerialTimeout(unsigned int milliseconds) {
  core::SerialTimeout(&packet_, bus_address_, milliseconds);
  return WritePacket(serial_fd_, &packet_);
}

bool MotorController::SetBaudRate(BaudRate baud_rate) {
  core::SetBaudRate(&packet_, bus_address_, baud_rate);
  bool result = WritePacket(serial_fd_, &packet_);
  SetTTYBaudRate(serial_fd_, baud_rate);
  return result;
}

bool MotorController::SetRamping(RampLevel level) {
  core::SetRamping(&packet_, bus_address_, level);
  return WritePacket(serial_fd_, &packet_);
}

bool MotorController::SetDeadband(uint8_t threshold) {
  core::SetDeadband(&packet_, bus_address_, threshold);
  return WritePacket(serial_fd_, &packet_);
}

} // namespace core
} // namespace apollo

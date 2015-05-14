#ifndef APOLLO_CORE_MOTOR_DEFINITIONS_H_
#define APOLLO_CORE_MOTOR_DEFINITIONS_H_

#include <cstdint>
#include <string>

namespace apollo {
namespace core {

// Each of the following pairs corresponds to a unique motor controller in the
// real word. Each pair is a string specifying the path that identifies the
// serial port on the beaglebone to which the motor controller is connected and
// a uint8 which is the address of the motor controller on the that serial bus.
//
// XXX: IMPORTANT! - Every motor should have a corresponding KillMotor(...) call
// in the SafeExit() function defined in safe_exit.h.

// Wheel motor 0.
static const std::string serial_tty_path_wheel_motor_0_ = "/dev/ttyO1";
static const uint8_t controller_address_wheel_motor_0_ = 128;

// Wheel motor 1.
static const std::string serial_tty_path_wheel_motor_1_ = "/dev/ttyO1";
static const uint8_t controller_address_wheel_motor_1_ = 128;

// Digger wheel motor.
static const std::string serial_tty_path_digger_motor_ = "/dev/ttyO1";
static const uint8_t controller_address_digger_motor_ = 128;

// Digger wheel linear actuator.
static const std::string serial_tty_path_vertical_motor_ = "/dev/ttyO1";
static const uint8_t controller_address_vertical_motor_ = 128;

} // namespace core
} // namespace apollo

#endif // APOLLO_CORE_MOTOR_DEFINITIONS_H_

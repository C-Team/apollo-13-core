#ifndef APOLLO_CORE_MOTOR_DEFINITIONS_H_
#define APOLLO_CORE_MOTOR_DEFINITIONS_H_

#include <cstdint>
#include <string>

namespace apollo {
namespace core {

////////////////////////////////////////////////////////////////////////////////
///////////////////////////// Motor Controlllers ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Each of the following pairs corresponds to a unique motor controller in the
// real word. Each pair is a string specifying the path that identifies the
// serial port on the beaglebone to which the motor controller is connected and
// a uint8 which is the address of the motor controller on the that serial bus.
//
// XXX: IMPORTANT! - Every motor should have a corresponding KillMotor(...) call
// in the SafeExit() function defined in safe_exit.h.

// Wheel motor 0.
static const std::string kSerialTTYPathWheelMotor0 = "/dev/ttyO1";
static const uint8_t kControllerAddressWheelMotor0 = 130;

// Wheel motor 1.
static const std::string kSerialTTYPathWheelMotor1 = "/dev/ttyO1";
static const uint8_t kControllerAddressWheelMotor1 = 129;

// Digger wheel motor and linear actuator.
static const std::string kSerialTTYPathDiggerMotor = "/dev/ttyO1";
static const uint8_t kControllerAddressDiggerMotor = 128;

// Conveyor motors controller.
static const std::string kSerialTTYPathConveyorMotor = "/dev/ttyO1";
static const uint8_t kControllerAddressConveyorMotor = 129;

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// Feedback Potentiometer /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// NOTE: Not a serial TTY like the above paths.
static const std::string kFeedbackPotentiometerFile = "/sys/devices/ocp.3/helper.16/AIN5";

} // namespace core
} // namespace apollo

#endif // APOLLO_CORE_MOTOR_DEFINITIONS_H_

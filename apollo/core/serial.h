#ifndef APOLLO_CORE_SERIAL_H_
#define APOLLO_CORE_SERIAL_H_

#include <cstdint>
#include <cstdio>

namespace apollo {
namespace core {

struct SerialPacket {
  uint8_t address;
  uint8_t command;
  uint8_t data;
  uint8_t checksum;
};

enum class BaudRate {
  BR2400,
  BR9600,
  BR19200,
  BR38400,
  BR115200,
};

enum class RampLevel {
  R1_4,
  R1_8,
  R1_12,
};

void CreateChecksum(SerialPacket* packet);

bool WritePacket(int fd, SerialPacket* packet);

// Helpers create fully valid packets with checksum included.
void DriveForwardMotor1(SerialPacket* packet, uint8_t address, uint8_t speed);

void DriveBackwardMotor1(SerialPacket* packet, uint8_t address, uint8_t speed);

void MinVoltage(SerialPacket* packet, uint8_t address, float volts);

void MaxVoltage(SerialPacket* packet, uint8_t address, float volts);

void DriveForwardMotor2(SerialPacket* packet, uint8_t address, uint8_t speed);

void DriveBackwardMotor2(SerialPacket* packet, uint8_t address, uint8_t speed);

void DriveForwardMixed(SerialPacket* packet, uint8_t address, uint8_t speed);

void DriveBackwardMixed(SerialPacket* packet, uint8_t address, uint8_t speed);

void TurnRightMixed(SerialPacket* packet, uint8_t address, uint8_t speed);

void TurnLeftMixed(SerialPacket* packet, uint8_t address, uint8_t speed);

void SerialTimeout(SerialPacket* packet, uint8_t address, unsigned int milliseconds);

void SetBaudRate(SerialPacket* packet, uint8_t address, BaudRate baud_rate);

void SetRamping(SerialPacket* packet, uint8_t address, RampLevel level);

void SetDeadband(SerialPacket* packet, uint8_t address, uint8_t threshold);

////////////////////////////////////////////////////////////////////////////////
//////////////////////////// Non-Motor Functions ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void SetTTYBaudRate(int fd, BaudRate baud_rate);

} // namespace core
} // namespace apollo

#endif // APOLLO_CORE_SERIAL_H_

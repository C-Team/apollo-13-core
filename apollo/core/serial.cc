#include "apollo/core/serial.h"

#include <termios.h>
#include <unistd.h>

namespace apollo {
namespace core {

void CreateChecksum(SerialPacket* packet) {
  packet->checksum = (packet->address + 
                      packet->command + 
                      packet->data) & 0b01111111;
}

bool WritePacket(int fd, SerialPacket* packet) {
  const size_t packet_size = sizeof(SerialPacket);
  return packet_size == write(fd, packet, packet_size);
}

void DriveForwardMotor1(SerialPacket* packet, uint8_t address, uint8_t speed) {
  packet->address = address;
  packet->command = 0;
  packet->data = speed;
  CreateChecksum(packet);
}

void DriveBackwardMotor1(SerialPacket* packet, uint8_t address, uint8_t speed) {
  packet->address = address;
  packet->command = 1;
  packet->data = speed;
  CreateChecksum(packet);
}

void MinVoltage(SerialPacket* packet, uint8_t address, float volts) {
  packet->address = address;
  packet->command = 2;
  packet->data = static_cast<uint8_t>((volts - 6) * 5);
  CreateChecksum(packet);
}

void MaxVoltage(SerialPacket* packet, uint8_t address, float volts) {
  packet->address = address;
  packet->command = 3;
  packet->data = static_cast<uint8_t>(volts * 5.12);
  CreateChecksum(packet);
}

void DriveForwardMotor2(SerialPacket* packet, uint8_t address, uint8_t speed) {
  packet->address = address;
  packet->command = 4;
  packet->data = speed;
  CreateChecksum(packet);
}

void DriveBackwardMotor2(SerialPacket* packet, uint8_t address, uint8_t speed) {
  packet->address = address;
  packet->command = 5;
  packet->data = speed;
  CreateChecksum(packet);
}

void DriveForwardMixed(SerialPacket* packet, uint8_t address, uint8_t speed) {
  packet->address = address;
  packet->command = 8;
  packet->data = speed;
  CreateChecksum(packet);
}

void DriveBackwardMixed(SerialPacket* packet, uint8_t address, uint8_t speed) {
  packet->address = address;
  packet->command = 9;
  packet->data = speed;
  CreateChecksum(packet);
}

void TurnRightMixed(SerialPacket* packet, uint8_t address, uint8_t speed) {
  packet->address = address;
  packet->command = 10;
  packet->data = speed;
  CreateChecksum(packet);
}

void TurnLeftMixed(SerialPacket* packet, uint8_t address, uint8_t speed) {
  packet->address = address;
  packet->command = 11;
  packet->data = speed;
  CreateChecksum(packet);
}

void SerialTimeout(SerialPacket* packet, uint8_t address, unsigned int milliseconds) {
  packet->address = address;
  packet->command = 14;
  packet->data = static_cast<uint8_t>(milliseconds / 100);
  CreateChecksum(packet);
}

void SetBaudRate(SerialPacket* packet, uint8_t address, BaudRate baud_rate) {
  packet->address = address;
  packet->command = 15;
  switch (baud_rate) {
    case BaudRate::BR2400:
      packet->data = 1;
      break;
    case BaudRate::BR9600:
      packet->data = 2;
      break;
    case BaudRate::BR19200:
      packet->data = 3;
      break;
    case BaudRate::BR38400:
      packet->data = 4;
      break;
    case BaudRate::BR115200:
      packet->data = 5;
      break;
  }
  CreateChecksum(packet);
}

void SetRamping(SerialPacket* packet, uint8_t address, RampLevel level) {
  packet->address = address;
  packet->command = 16;
  switch (level) {
    case RampLevel::R1_4:
      packet->data = 1;
      break;
    case RampLevel::R1_8:
      packet->data = 2;
      break;
    case RampLevel::R1_12:
      packet->address = 3;
      break;
  }
  CreateChecksum(packet);
}

void SetDeadband(SerialPacket* packet, uint8_t address, uint8_t threshold) {
  packet->address = address;
  packet->command = 17;
  packet->data = threshold;
  CreateChecksum(packet);
}

////////////////////////////////////////////////////////////////////////////////
//////////////////////////// Non-Motor Functions ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void SetTTYBaudRate(int fd, BaudRate baud_rate) {
  speed_t raw_baud_rate;
  switch (baud_rate) {
    case BaudRate::BR2400:
      raw_baud_rate = B2400;
      break;
    case BaudRate::BR9600:
      raw_baud_rate = B9600;
      break;
    case BaudRate::BR19200:
      raw_baud_rate = B19200;
      break;
    case BaudRate::BR38400:
      raw_baud_rate = B38400;
      break;
    case BaudRate::BR115200:
      raw_baud_rate = B115200;
      break;
  }

  struct termios serial_attr;
  tcgetattr(fd, &serial_attr);
  cfsetospeed(&serial_attr, raw_baud_rate);
  tcsetattr(fd, TCSADRAIN, &serial_attr);
}

} // namespace core
} // namespace apollo

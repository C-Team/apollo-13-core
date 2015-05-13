#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include "apollo/core/serial.h"
#include "apollo/core/motor_controller.h"

using apollo::core::SerialPacket;
using apollo::core::CreateChecksum;
using apollo::core::WritePacket;
using apollo::core::DriveForwardMotor1;
using apollo::core::MotorController;

static const char* kTTYPath = "/dev/ttyO1";
static const uint8_t bus_address = 128;

void write_shit(void) {
  MotorController controller(kTTYPath, bus_address);
  if (!controller.Init()) {
    printf("Starting motor controller failed.\n");
  }
  controller.DriveForwardMixed(40);
  controller.TurnLeftMixed(20);
  sleep(2);
  controller.DriveForwardMixed(0);
  controller.TurnLeftMixed(0);
}

int main() {
  printf("Hello world!\n");
  write_shit();
  return 0;
}

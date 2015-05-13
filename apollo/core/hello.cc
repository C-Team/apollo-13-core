#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include "apollo/core/serial.h"

using apollo::core::SerialPacket;
using apollo::core::CreateChecksum;
using apollo::core::WritePacket;
using apollo::core::DriveForwardMotor1;

static const char* kTTYPath = "/dev/ttyO1";

void write_shit(void) {
  int fd = open(kTTYPath, O_WRONLY);

  SerialPacket packet;
  DriveForwardMotor1(&packet, 128, 20);
  if (!WritePacket(fd, &packet)) {
    printf("Writing packet failed\n");
  }
  sleep(2);
  DriveForwardMotor1(&packet, 128, 0);
  WritePacket(fd, &packet);

  close(fd);
}

int main() {
  printf("Hello world!\n");
  write_shit();
  return 0;
}

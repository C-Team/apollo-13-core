#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include "apollo/core/serial.h"
#include "apollo/core/digger_controller.h"
#include "apollo/core/feedback_potentiometer.h"
#include "apollo/core/motor_controller.h"

using apollo::core::SerialPacket;
using apollo::core::CreateChecksum;
using apollo::core::WritePacket;
using apollo::core::DriveForwardMotor1;
using apollo::core::MotorController;
using apollo::core::FeedbackPotentiometer;
using apollo::core::DiggerController;

static const char* kTTYPath = "/dev/ttyO1";
static const uint8_t bus_address = 128;

int do_shit() {
  DiggerController controller;
  if (!controller.Init()) {
    printf("Starting motor controller failed.\n");
    return -1;
  }
  controller.SetVerticalPosition(2);
  while (true) {}
  return 0;
}

void write_shit() {
  MotorController controller(kTTYPath, bus_address);
  if (!controller.Init()) {
    printf("Starting motor controller failed.\n");
  }
  controller.SetSpeed(10);
  controller.SetDirection(10);
  sleep(2);
  controller.SetSpeed(10);
  controller.SetDirection(-10);
  sleep(2);
  controller.SetSpeed(-10);
  controller.SetDirection(-10);
  sleep(2);
  controller.SetSpeed(-10);
  controller.SetDirection(10);
  sleep(2);
  controller.SetSpeed(0);
  controller.SetDirection(0);
}

int read_shit() {
  FeedbackPotentiometer feedback;
  if (!feedback.Init()) {
    return -1;
  }
  for (int i = 0; i < 5; i++) {
    printf("Current reading = %d\n", feedback.ReadCurrentValue());
    sleep(1);
  }
  return 0;
}

int main() {
  return do_shit();
}

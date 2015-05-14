#include <csignal>
#include <cstdio>
#include <cstdlib>
#include "apollo/core/motor_controller.h"
#include "apollo/core/safe_exit.h"
#include "apollo/remote/network_packet.h"
#include "apollo/remote/connection_manager.h"

using std::string;
using apollo::core::MotorController;
using apollo::remote::Command;
using apollo::remote::CommandPacket;
using apollo::remote::ConnectionManager;

static const char* kTTYPath = "/dev/ttyO1";
static const uint8_t bus_address = 128;
static const string address = "192.168.7.2";
static const int port = 9001;

bool noop() {
  return true;
}

bool handle_error(MotorController* controller) {
  return controller->SetSpeed(0) && controller->SetDirection(0);
}

bool handle_packet(MotorController* controller, CommandPacket* packet) {
  switch (static_cast<Command>(packet->command)) {
    case Command::SET_SPEED:
      printf("Set speed to %d\n", packet->data_0);
      return controller->SetSpeed(packet->data_0);
    case Command::SET_DIRECTION:
      printf("Set direction to %d\n", packet->data_0);
      return controller->SetDirection(packet->data_0);
  }
  return false;
}

bool handle_end(MotorController* controller) {
  return controller->SetSpeed(0) && controller->SetDirection(0);
}

int main() {
  using namespace std::placeholders;

  apollo::core::SetUpSafeExit();

  MotorController controller(kTTYPath, bus_address);
  if (!controller.Init()) {
    printf("Encountered serial error.\n");
    return -1;
  }
  controller.DriveForwardMixed(0);
  controller.TurnLeftMixed(0);

  ConnectionManager connection_manager(address, port);
  connection_manager.set_on_start(&noop);
  connection_manager.set_on_failure(std::bind(&handle_error, &controller));
  connection_manager.set_handler(std::bind(&handle_packet, &controller, _1));
  connection_manager.set_on_end(std::bind(&handle_end, &controller));
  if (!connection_manager.Start()) {
    return -1;
  }

  return 0;
}

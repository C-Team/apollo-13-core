#include <csignal>
#include <cstdio>
#include <cstdlib>
#include "apollo/core/safe_exit.h"
#include "apollo/remote/network_packet.h"
#include "apollo/remote/connection_manager.h"
#include "apollo/core/wheel_controller.h"
#include "apollo/core/digger_controller.h"

using std::string;
using apollo::remote::Command;
using apollo::remote::CommandPacket;
using apollo::remote::ConnectionManager;
using apollo::core::WheelController;
using apollo::core::DiggerController;

static const char* kTTYPath = "/dev/ttyO1";
static const uint8_t bus_address = 128;
static const string address = "192.168.0.103";
static const int port = 9001;

struct RobotController {
  DiggerController digger_controller;
  WheelController wheel_controller;
};

bool noop() {
  return true;
}

bool handle_error(RobotController* controller) {
  return controller->wheel_controller.SetSpeed(0) 
      && controller->wheel_controller.SetDirection(0)
      && controller->digger_controller.SetSpeed(0)
      && controller->digger_controller.SetSpeed(0);
}

bool handle_packet(RobotController* controller, CommandPacket* packet) {
  switch (static_cast<Command>(packet->command)) {
    case Command::SET_SPEED:
      printf("Set speed to %d\n", packet->data_0);
      return controller->wheel_controller.SetSpeed(packet->data_0);
    case Command::SET_DIRECTION:
      printf("Set direction to %d\n", packet->data_0);
      return controller->wheel_controller.SetDirection(packet->data_0);
    case Command::SET_DIGGER_WHEEL_SPEED:
      printf("Set digger wheel speed to %d\n", packet->data_0);
      return controller->digger_controller.SetSpeed(packet->data_0);
    case Command::SET_DIGGER_VERTICAL_SPEED:
      printf("Set digger vertical speed to %d\n", packet->data_0);
      return controller->digger_controller.SetSpeed(packet->data_0);
    case Command::SET_DIGGER_VERTICAL_POSITION:
      printf("Set digger vertical position to %d\n", packet->data_0);
      return controller->digger_controller.SetDirection(packet->data_0);
  }
  return false;
}

bool handle_end(RobotController* controller) {
  return controller->wheel_controller.SetSpeed(0) 
      && controller->wheel_controller.SetDirection(0)
      && controller->digger_controller.SetSpeed(0)
      && controller->digger_controller.SetSpeed(0);
}

int main() {
  using namespace std::placeholders;

  apollo::core::SetUpSafeExit();

  RobotController controller;
  if (!controller.wheel_controller.Init() || !controller.digger_controller.Init()) {
    printf("Encountered serial error.\n");
    return -1;
  }
  controller.wheel_controller.SetSpeed(0);
  controller.wheel_controller.SetDirection(0);
  controller.digger_controller.SetSpeed(0);
  controller.digger_controller.SetSpeed(0);
  controller.digger_controller.SetDirection(0);
  controller.digger_controller.SetDirection(0);

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

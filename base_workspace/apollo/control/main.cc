#include <csignal>
#include <cstdio>
#include <cstdlib>
#include "apollo/core/conveyor_controller.h"
#include "apollo/core/digger_controller.h"
#include "apollo/core/safe_exit.h"
#include "apollo/core/wheel_controller.h"
#include "apollo/remote/connection_manager.h"
#include "apollo/remote/network_packet.h"

using std::string;
using apollo::remote::Command;
using apollo::remote::CommandPacket;
using apollo::remote::ConnectionManager;
using apollo::core::WheelController;
using apollo::core::DiggerController;
using apollo::core::ConveyorController;

static const int port = 9001;

struct RobotController {
  DiggerController digger_controller;
  WheelController wheel_controller;
  ConveyorController conveyor_controller;
};

bool noop() {
  return true;
}

bool handle_error(RobotController* controller) {
  return controller->wheel_controller.SetSpeed(0) 
      && controller->wheel_controller.SetDirection(0)
      && controller->digger_controller.SetWheelSpeed(0)
      && controller->digger_controller.SetVerticalSpeed(0)
      && controller->conveyor_controller.TurnOffConveyor1()
      && controller->conveyor_controller.TurnOffConveyor2();
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
      return controller->digger_controller.SetWheelSpeed(packet->data_0);
    case Command::SET_DIGGER_VERTICAL_SPEED:
      printf("Set digger vertical speed to %d\n", packet->data_0);
      if (packet->data_0 == 0) {
      }
      return controller->digger_controller.SetVerticalSpeed(packet->data_0);
    case Command::SET_DIGGER_VERTICAL_POSITION:
      // printf("Set digger vertical position to %d\n", packet->data_0);
      printf("Current position is %d\n", controller->digger_controller.ReadCurrentValue());
      return true; // controller->digger_controller.SetVerticalSpeed(packet->data_0);
    case Command::SET_CONVEYOR_1_SPEED:
      printf("Set conveyor 1 speed to %d\n", packet->data_0);
      return controller->conveyor_controller.SetSpeedConveyor1(packet->data_0);
    case Command::SET_CONVEYOR_2_SPEED:
      printf("Set conveyor 1 speed to %d\n", packet->data_0);
      return controller->conveyor_controller.SetSpeedConveyor2(packet->data_0);
    case Command::SET_CONVEYOR_1_STATUS:
      if (packet->data_0 == 0) {
        printf("Turning off conveyor 1 %d\n", packet->data_0);
        return controller->conveyor_controller.TurnOffConveyor1();
      } else {
        printf("Turning on conveyor 1 %d\n", packet->data_0);
        return controller->conveyor_controller.TurnOnConveyor1();
      }
    case Command::SET_CONVEYOR_2_STATUS:
      if (packet->data_0 == 0) {
        printf("Turning off conveyor 2 %d\n", packet->data_0);
        return controller->conveyor_controller.TurnOffConveyor2();
      } else {
        printf("Turning on conveyor 2 %d\n", packet->data_0);
        return controller->conveyor_controller.TurnOnConveyor2();
      }
  }
  return false;
}

bool handle_end(RobotController* controller) {
  return controller->wheel_controller.SetSpeed(0) 
      && controller->wheel_controller.SetDirection(0)
      && controller->digger_controller.SetWheelSpeed(0)
      && controller->digger_controller.SetVerticalSpeed(0)
      && controller->conveyor_controller.TurnOffConveyor1()
      && controller->conveyor_controller.TurnOffConveyor2();
}

int main() {
  using namespace std::placeholders;

  apollo::core::SetUpSafeExit();

  RobotController controller;
  if (!controller.wheel_controller.Init() 
      || !controller.digger_controller.Init() 
      || !controller.conveyor_controller.Init()) {
    printf("Encountered serial error.\n");
    return -1;
  }
  controller.wheel_controller.SetSpeed(0);
  controller.wheel_controller.SetDirection(0);
  controller.digger_controller.SetVerticalSpeed(0);
  controller.digger_controller.SetWheelSpeed(0);

  ConnectionManager connection_manager(port);
  connection_manager.set_on_start(&noop);
  connection_manager.set_on_failure(std::bind(&handle_error, &controller));
  connection_manager.set_handler(std::bind(&handle_packet, &controller, _1));
  connection_manager.set_on_end(std::bind(&handle_end, &controller));
  if (!connection_manager.Start()) {
    return -1;
  }

  return 0;
}

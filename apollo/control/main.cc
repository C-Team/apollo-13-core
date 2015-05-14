#include "apollo/core/motor_controller.h"
#include "apollo/remote/network_packet.h"
#include "apollo/remote/packet_manager.h"

using std::string;
using apollo::core::MotorController;
using apollo::remote::Command;
using apollo::remote::CommandPacket;
using apollo::remote::PacketManager;

static const char* kTTYPath = "/dev/ttyO1";
static const uint8_t bus_address = 128;
static const string address = "192.168.7.2";
static const int port = 9001;

int main() {
  MotorController controller(kTTYPath, bus_address);
  if (!controller.Init()) {
    printf("Encountered serial error.\n");
    return -1;
  }
  controller.DriveForwardMixed(0);
  controller.TurnLeftMixed(0);

  PacketManager manager(address, port);
  if (!manager.Init()) {
    printf("Encountered network error.\n");
    return -1;
  }

  CommandPacket packet;
  while (true) {
    manager.ReadPacket(&packet);
    switch (static_cast<Command>(packet.command)) {
      case Command::SET_SPEED:
        printf("Set speed to %d\n", packet.data_0);
        controller.SetSpeed(packet.data_0);
        break;
      case Command::SET_DIRECTION:
        printf("Set direction to %d\n", packet.data_0);
        controller.SetDirection(packet.data_0);
        break;
    }
  }
  return 0;
}

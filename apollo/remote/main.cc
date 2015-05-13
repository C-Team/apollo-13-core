#include <cstdio>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include "apollo/remote/network_packet.h"
#include "apollo/remote/packet_manager.h"

using std::string;
using apollo::remote::Command;
using apollo::remote::CommandPacket;
using apollo::remote::PacketManager;

static const string address = "";
static const int port = 9001;

int main() {
  PacketManager manager(address, port);
  if (!manager.Init()) {
    return -1;
  }

  CommandPacket packet;
  while (true) {
    manager.ReadPacket(&packet);
    switch (static_cast<Command>(packet.command)) {
      case Command::DRIVE_FORWARD:
        printf("Drive Forward at %d\n", packet.data_0);
        break;
      case Command::DRIVE_BACKWARD:
        printf("Drive Backward at %d\n", packet.data_0);
        break;
      case Command::TURN_LEFT:
        printf("Turning Left at %d\n", packet.data_0);
        break;
      case Command::TURN_RIGHT:
        printf("Turning Right at %d\n", packet.data_0);
        break;
    }
  }

  return 0;
}

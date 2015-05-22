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

static const string address = "192.168.7.2";
static const int port = 9001;

int main() {
  PacketManager manager(port);
  if (!manager.Init()) {
    return -1;
  }

  CommandPacket packet;
  while (true) {
    manager.ReadPacket(&packet);
    switch (static_cast<Command>(packet.command)) {
      case Command::SET_SPEED:
        printf("Set speed to %d\n", packet.data_0);
        break;
      case Command::SET_DIRECTION:
        printf("Set direction to %d\n", packet.data_0);
        break;
      default:
        break;
    }
  }

  return 0;
}

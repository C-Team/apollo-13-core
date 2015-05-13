#include "apollo/remote/packet_manager.h"

#include <cstdio>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>

namespace apollo {
namespace remote {

using std::string;

namespace {
void GetSockAddr(const string& str_address, int port, sockaddr_in* address) {
  address->sin_family = AF_INET;
  address->sin_port = htons(port);
  inet_pton(AF_INET, str_address.c_str(), &address->sin_addr.s_addr);
}
} // namespace

PacketManager::PacketManager(const string& address, int port) 
  : address_(address), port_(port) {}

PacketManager::~PacketManager() {
  close(fd_);
  close(sock_);
}

bool PacketManager::Init() {
  sockaddr_in address;
  socklen_t sock_len = sizeof(sockaddr_in);
  GetSockAddr(address_, port_, &address);

  sock_ = socket(AF_INET, SOCK_STREAM, 0);
  if (bind(sock_, (sockaddr*) &address, sizeof(sockaddr_in)) < 0) {
    printf("Error binding\n");
    return false;
  }
  if (listen(sock_, kQueueSize) < 0) {
    printf("Error listening\n");
    return false;
  }

  fd_ = accept(sock_, (sockaddr*) &address, &sock_len);

  return true;
}

bool PacketManager::ReadPacket(CommandPacket* packet) {
  return read(fd_, packet, sizeof(CommandPacket)) == sizeof(CommandPacket);
}

} // namespace remote
} // namespace apollo

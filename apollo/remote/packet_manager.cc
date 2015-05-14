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
  GetSockAddr(address_, port_, &address_struct_);

  sock_ = socket(AF_INET, SOCK_STREAM, 0);
  if (bind(sock_, (sockaddr*) &address_struct_, sizeof(sockaddr_in)) < 0) {
    printf("Error binding\n");
    return false;
  }
  if (listen(sock_, kQueueSize) < 0) {
    printf("Error listening\n");
    return false;
  }

  return true;
}

bool PacketManager::IsConnectionValid() {
  uint8_t check_value = 0xff;
  return send(fd_, &check_value, 1, MSG_NOSIGNAL) >= 0;
}

bool PacketManager::Connect() {
  if (fd_ >= 0) {
    close(fd_);
  }
  socklen_t sock_len = sizeof(sockaddr_in);
  fd_ = accept(sock_, (sockaddr*) &address_struct_, &sock_len);
  if (fd_ < 0) {
    return false;
  } else {
    return true;
  }
}

bool PacketManager::ReadPacket(CommandPacket* packet) {
  return read(fd_, packet, sizeof(CommandPacket)) == sizeof(CommandPacket);
}

} // namespace remote
} // namespace apollo

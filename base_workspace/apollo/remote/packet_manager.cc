#include "apollo/remote/packet_manager.h"

#include <cstdio>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include "apollo/core/safe_exit.h"

namespace apollo {
namespace remote {

using std::string;

namespace {
void GetSockAddr(int port, sockaddr_in* address) {
  address->sin_family = AF_INET;
  address->sin_addr.s_addr = htonl(INADDR_ANY);
  address->sin_port = htons(port);
}
} // namespace

PacketManager::PacketManager(int port) 
  : port_(port) {}

PacketManager::~PacketManager() {
  close(fd_);
  close(sock_);
}

bool PacketManager::Init() {
  GetSockAddr(port_, &address_struct_);

  sock_ = socket(AF_INET, SOCK_STREAM, 0);
  if (bind(sock_, (sockaddr*) &address_struct_, sizeof(sockaddr_in)) < 0) {
    printf("Error binding\n");
    close(sock_);
    return false;
  }
  core::sockfd = sock_;
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
  printf("Accepted connection.\n");
  if (fd_ < 0) {
    return false;
  } else {
    return true;
  }
}

bool PacketManager::ReadPacket(CommandPacket* packet) {
  printf("About to read\n");
  int result = read(fd_, packet, sizeof(CommandPacket));
  printf("Packet read, size = %d\n", result);
  return result == sizeof(CommandPacket);
}

} // namespace remote
} // namespace apollo

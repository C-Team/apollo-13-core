#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

static const char* kTTYPath = "/dev/ttyO1";

void set_baud_rate(int fd, speed_t baud_rate) {
  struct termios serial_attr;
  tcgetattr(fd, &serial_attr);
  cfsetospeed(&serial_attr, baud_rate);
  tcsetattr(fd, TCSADRAIN, &serial_attr);
}

void write_shit(void) {
  const char value = 40;
  const char off = 64;
  int fd = open(kTTYPath, O_WRONLY);
  set_baud_rate(fd, B38400);
  for (int i = 0; i < 10; i++) {
    write(fd, &value, 1);
    sleep(1);
    write(fd, &off, 1);
    sleep(1);
  }
  close(fd);
}

int main() {
  printf("Hello world!\n");
  write_shit();
  return 0;
}

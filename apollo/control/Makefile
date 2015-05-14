CC= arm-linux-gnueabi-gcc
CXX= arm-linux-gnueabi-g++
LDFLAGS= -lgcc -lc -lgcc -lsupc++ -lstdc++ -static
CXXFLAGS= -I ../.. -std=c++11 -mfloat-abi=soft

control: main.o ../remote/packet_manager.o ../core/motor_controller.o  ../core/serial.o
	$(CXX) $(CXXFLAGS) main.o ../remote/packet_manager.o ../core/motor_controller.o ../core/serial.o -o $@ $(LDFLAGS)

main.o: main.cc ../remote/packet_manager.h ../remote/network_packet.h ../core/motor_controller.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

.PHONY: all

all:
	control

.PHONY: clean

clean:
	rm -rf *.o control

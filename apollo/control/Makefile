CC= arm-linux-gnueabi-gcc
CXX= arm-linux-gnueabi-g++
LDFLAGS= -lgcc -lc -lgcc -lsupc++ -lstdc++ -pthread -static
CXXFLAGS= -I ../.. -std=c++11 -mfloat-abi=soft

control: main.o ../core/libcore.a ../remote/libremote.a
	$(CXX) $(CXXFLAGS) main.o -o $@ $(LDFLAGS) -L../core -lcore -L../remote -lremote

main.o: main.cc ../remote/packet_manager.h ../remote/network_packet.h ../core/motor_controller.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

.PHONY: all

all:
	control

.PHONY: clean

clean:
	rm -rf *.o control

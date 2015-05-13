CC= arm-linux-gnueabi-gcc
CXX= arm-linux-gnueabi-g++
LDFLAGS= -lgcc -lc -lgcc -lsupc++ -lstdc++ -static
CXXFLAGS= -I ../.. -std=c++11 -mfloat-abi=soft

remote: main.o packet_manager.o
	$(CXX) $(CXXFLAGS) main.o packet_manager.o -o $@ $(LDFLAGS)

main.o: main.cc packet_manager.h network_packet.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

packet_manager.o: packet_manager.cc packet_manager.h network_packet.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

.PHONY: all

all:
	remote

.PHONY: clean

clean:
	rm -rf *.o remote

CC= arm-linux-gnueabi-gcc
CXX= arm-linux-gnueabi-g++
LDFLAGS= -lgcc -lc -lgcc -lsupc++
CXXFLAGS= -I ../.. -std=c++11

hello: hello.o serial.o
	$(CXX) $(CXXFLAGS) hello.o serial.o -o $@ $(LDFLAGS)

hello.o: hello.cc serial.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

serial.o: serial.cc serial.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

motor_controller.o: motor_controller.cc motor_controller.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

.PHONY: all

all:
	hello

.PHONY: clean

clean:
	rm -rf *.o hello

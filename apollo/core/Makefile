CC= arm-linux-gnueabi-gcc
CXX= arm-linux-gnueabi-g++
LDFLAGS= -lgcc -lc -lgcc -lsupc++ -lstdc++ -static
CXXFLAGS= -I ../.. -std=c++11 -mfloat-abi=soft

hello: hello.o motor_controller.o serial.o
	$(CXX) $(CXXFLAGS) hello.o motor_controller.o serial.o -o $@ $(LDFLAGS)

hello.o: hello.cc serial.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

serial.o: serial.cc serial.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

motor_controller.o: motor_controller.cc motor_controller.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

wheel_controller.o: wheel_controller.cc wheel_controller.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

.PHONY: all

all:
	hello

.PHONY: clean

clean:
	rm -rf *.o hello

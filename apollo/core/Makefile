CC= arm-linux-gnueabi-gcc
CXX= arm-linux-gnueabi-g++
LDFLAGS= -lgcc -lc -lgcc -lsupc++ -lstdc++ -pthread -static
CXXFLAGS= -I ../.. -std=c++11 -mfloat-abi=soft

all: libcore.a hello

hello: hello.o motor_controller.o serial.o
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS) -L. -lcore

hello.o: hello.cc serial.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

serial.o: serial.cc serial.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

motor_controller.o: motor_controller.cc motor_controller.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

feedback_potentiometer.o: feedback_potentiometer.cc feedback_potentiometer.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

wheel_controller.o: wheel_controller.cc wheel_controller.h motor_definitions.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

digger_controller.o: digger_controller.cc digger_controller.h motor_definitions.h position_controller.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

conveyor_controller.o: conveyor_controller.cc conveyor_controller.h motor_definitions.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

safe_exit.o: safe_exit.cc safe_exit.h motor_definitions.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

position_controller.o: position_controller.cc position_controller.h
	$(CXX) -c $(CXXFLAGS) $< -o $@ -pthread

libcore.a: motor_controller.o serial.o wheel_controller.o digger_controller.o safe_exit.o feedback_potentiometer.o position_controller.o conveyor_controller.o
	ar -r $@ $^

.PHONY: clean

clean:
	rm -rf *.o *.a hello

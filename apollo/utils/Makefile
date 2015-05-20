CC= arm-linux-gnueabi-gcc
CXX= arm-linux-gnueabi-g++
LDFLAGS= -lgcc -lc -lgcc -lsupc++ -lstdc++ -static -pthread -Wl,--no-as-needed -Wl,--whole-archive -lpthread -Wl,--no-whole-archive
CXXFLAGS= -I ../.. -std=c++11 -mfloat-abi=soft

all: libutils.a

file.o: file.cc file.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

libutils.a: file.o
	ar -r $@ $^

.PHONY: clean

clean:
	rm -rf *.o *.a

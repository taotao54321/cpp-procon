.PHONY: all clean

CXX := g++
CXXFLAGS := \
    -std=c++14 \
    -Wall -Wextra \
    -Wconditionally-supported \
    -Wconversion \
    -Wduplicated-cond \
    -Wduplicated-branches \
    -Wextra-semi \
    -Wfloat-equal \
    -Wformat=2 \
    -Wlogical-op \
    -Wnull-dereference \
    -Wold-style-cast \
    -Wshadow \
    -Wundef \
    -Wuseless-cast \
    -Wvla \
    -Wzero-as-null-pointer-constant \
    -O2 \
    -I../../include/

TARGET := a.out

all: $(TARGET)

-include solve.d

$(TARGET): solve.o
	$(CXX) $(CXXFLAGS) $< -ltestu01 -ltestu01mylib -ltestu01probdist

%.o: %.c
	$(CXX) $(CXXFLAGS) -c -MMD -MP $<

clean:
	-$(RM) $(TARGET) *.o

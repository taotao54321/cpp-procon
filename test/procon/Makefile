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
    -Wswitch-default \
    -Wswitch-enum \
    -Wundef \
    -Wuseless-cast \
    -Wvla \
    -Wzero-as-null-pointer-constant \
    -g -fsanitize=undefined -D_GLIBCXX_DEBUG \
    -I../../include/
LDFLAGS :=

TARGET := a.out

all: $(TARGET)

-include solve.d

$(TARGET): solve.o
	$(CXX) $(CXXFLAGS) $< $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -MP $<

clean:
	-$(RM) $(TARGET) *.o

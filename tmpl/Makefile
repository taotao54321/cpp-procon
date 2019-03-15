.PHONY: all clean

CXX := g++
CXXFLAGS := \
    -std=c++14 \
    -Wall -Wextra \
    -Wconversion \
    -Wduplicated-cond \
    -Wduplicated-branches \
    -Wformat=2 \
    -Wlogical-op \
    -Wnull-dereference \
    -Wold-style-cast \
    -Wshadow \
    -Wzero-as-null-pointer-constant \
    -DPROCON_LOCAL

ifdef OPTIMIZE
    CXXFLAGS += -O2
else
    CXXFLAGS += -g -fsanitize=undefined -D_GLIBCXX_DEBUG
endif

TARGET := a.out

all: $(TARGET)

$(TARGET) : solve.cpp
	$(CXX) $(CXXFLAGS) $<

clean:
	-$(RM) $(TARGET)

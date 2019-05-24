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
    -pg \
    -DPROCON_LOCAL
LDFLAGS :=

ifdef OPTIMIZE
    CXXFLAGS += -O2
else
    CXXFLAGS += -g -fsanitize=undefined -D_GLIBCXX_DEBUG
endif

SRC_SOLVE := solve.cpp
SRCS := $(filter-out $(SRC_SOLVE),$(wildcard *.cpp))

TARGET := $(addprefix bin/,$(basename $(SRCS)))
ifneq ("$(wildcard $(SRC_SOLVE))","")
    TARGET += a.out
endif

all: $(TARGET)

a.out: $(SRC_SOLVE)
	$(CXX) $(CXXFLAGS) $< $(LDFLAGS)

bin/%: %.cpp
	mkdir -p -v bin
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

clean:
	-$(RM) $(TARGET) gmon.out

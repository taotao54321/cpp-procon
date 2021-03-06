.PHONY: all clean

CXX ?= g++

ifeq ($(CXX),g++)
    CXXFLAGS := \
        -std=c++17 \
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
        -Wvla \
        -Wzero-as-null-pointer-constant \
        -pg \
        -DPROCON_LOCAL
    ifdef OPTIMIZE
        CXXFLAGS += -O2
    else
        CXXFLAGS += -g3 -fsanitize=undefined -fno-sanitize-recover=all -D_GLIBCXX_DEBUG
    endif
else ifeq ($(CXX),clang++)
    CXXFLAGS := \
        -std=c++17 \
        -Wall -Wextra \
        -Wconversion \
        -Wextra-semi \
        -Wfloat-equal \
        -Wformat=2 \
        -Wno-sign-conversion \
        -Wnull-dereference \
        -Wold-style-cast \
        -Wshadow \
        -Wswitch-default \
        -Wswitch-enum \
        -Wundef \
        -Wvla \
        -Wzero-as-null-pointer-constant \
        -pg \
        -DPROCON_LOCAL
    ifdef OPTIMIZE
        CXXFLAGS += -O2
    else
        CXXFLAGS += -g3 -fsanitize=undefined -fno-sanitize-recover=all -D_GLIBCXX_DEBUG
    endif
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

CXX := g++
CXXFLAGS := -std=c++14 -Wall -Wextra -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wold-style-cast -Wshadow -Wformat=2 -DPROCON_LOCAL

ifdef OPTIMIZE
    CXXFLAGS += -O2
else
    CXXFLAGS += -g -fsanitize=undefined -D_GLIBCXX_DEBUG
endif

a.out : solve.cpp
	$(CXX) $(CXXFLAGS) $<

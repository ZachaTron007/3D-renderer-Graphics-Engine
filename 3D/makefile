# Compiler settings - Can be customized.
CC = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lSDL2

# Makefile settings - Can be customized.
APPNAME = 3D
EXT = .cpp
SRCDIR = src
OBJDIR = obj

SRC = $(shell find $(SRCDIR) -name "*.cpp")

Test:
	@echo $(SRC)

$(APPNAME):
	$(CC) $(CXXFLAGS) $(SRC) $(LDFLAGS)

run: $(APPNAME)
	./a.out
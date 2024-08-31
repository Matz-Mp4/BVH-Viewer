# Compiler and flags
CC = g++
CFLAGS = -Wall -g -std=c++17
LDFLAGS = -lGL -lGLU -lglut

# Directories
SRCDIR = src
BINDIR = bin

# Source files and target
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = $(BINDIR)/volumetric_viewer

# Rules
all: $(BINDIR) $(TARGET)

$(BINDIR):
	mkdir -p $(BINDIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	rmdir $(BINDIR)

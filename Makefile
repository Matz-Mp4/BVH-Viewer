# Compiler and flags
CC = g++
CFLAGS = -Wall -g -std=c++17
LDFLAGS = -Lthird_party 

# Directories
SRCDIR = src
BINDIR = bin
THIRDPARTYDIR = third_party

# Source files and target
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = $(BINDIR)/VolumetricViewer

# Rules
all: $(BINDIR) $(TARGET)

$(BINDIR):
	mkdir -p $(BINDIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -I$(THIRDPARTYDIR) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	rmdir $(BINDIR)

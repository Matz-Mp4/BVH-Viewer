linkTarget = TinyRayTracer

# Define the libraries that we need
LIBS = -lGL

# Define any flags
CFLAGS = -std=c++20 -Ofast

# Define the object files that we need to use
objects = $(patsubst %.cpp,%.o,$(wildcard ./src/**/*.cpp ./src/*.cpp))

# Define the rebuildables
rebuildables = $(objects) $(linkTarget)

# Rule to actually perform the build
$(linkTarget): $(objects)
	g++ -g -o bin/$(linkTarget) $(objects) $(LIBS) $(CFLAGS)

# Rule to create the .o (object) files
%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)
	
.PHONY: clean

clean:
	rm -f $(rebuildables)

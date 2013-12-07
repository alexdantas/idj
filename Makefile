# idj Makefile
#
# It is quite complex, sorry.
#
# With this makefile, you can run the following targets:
#
# $ make          Runs `make all`.
# $ make all      Builds everything on the project.
# $ make run      Runs the final built program.
# $ make dox      Creates Doxygen code documentation under `doc/`.
# $ make doxclean Clears the Doxygen code documentation.
# $ make clean    Cleans temporary files and the final executable.
# $ make libclean Cleans temporary files related to third-party libs.
#
# Also, if you want to see everything that's happening,
# allow verbose mode on any of the targets above:
#
# $ make V=1
#
# Have fun!

EXE = idj

CFLAGS   = -g `sdl-config --cflags`
CXXFLAGS = -Wall -Wextra -g `sdl-config --cflags`
LDFLAGS  = `sdl-config --libs` \
           -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL_gfx

# All third-party libraries I've used on the project
LIB_TMXPARSER = src/lib/TmxParser
LIB_TINYXML   = src/lib/TmxParser/tinyxml
LIB_ZLIB      = src/lib/TmxParser/zlib
LIB_BASE64    = src/lib/TmxParser/base64

LIBS_CFILES   = $(shell find  $(LIB_TMXPARSER) \
                              $(LIB_TINYXML)   \
                              $(LIB_ZLIB)      \
                              $(LIB_BASE64)    \
                              -maxdepth 1 -type f -name '*.c')

LIBS_CXXFILES =  $(shell find $(LIB_TMXPARSER) \
                              $(LIB_TINYXML)   \
                              $(LIB_ZLIB)      \
                              $(LIB_BASE64)    \
                              -maxdepth 1 -type f -name '*.cpp')

INCLUDE = -I$(LIB_TMXPARSER)   \
          -I$(LIB_TINYXML)     \
          -I$(LIB_ZLIB)        \
          -I$(LIB_BASE64)      \
          -I"/usr/include/SDL"

CC  = gcc
CXX = g++

# All C file sources of the project
CFILES   = $(shell find src -maxdepth 1 -type f -name '*.c')
COBJECTS = $(CFILES:.c=.o)

# All C++ file sources of the project
CXXFILES   = $(shell find src -maxdepth 1 -type f -name '*.cpp')
CXXOBJECTS = $(CXXFILES:.cpp=.o)

SOURCES = $(CFILES)   $(CXXFILES)
OBJECTS = $(COBJECTS) $(CXXOBJECTS)

LIBS_COBJECTS   = $(LIBS_CFILES:.c=.o)
LIBS_CXXOBJECTS = $(LIBS_CXXFILES:.cpp=.o)

LIBS_SOURCES    = $(LIBS_CFILES)   $(LIBS_CXXFILES)
LIBS_OBJECTS    = $(LIBS_COBJECTS) $(LIBS_CXXOBJECTS) \
                  src/lib/SDL_Config/SDL_config.o

# Allowing to mute execution
ifdef V
MUTE =
VTAG = -v
else
MUTE = @
endif

################################################################################
# Don't try to understand this
# It keeps a counter on how much source files we still need to compile.
# It was taken from the interwebs and I've still not figured out how it works.

# BUILD is initially undefined
ifndef BUILD

# max equals 256 x's
sixteen := x x x x x x x x x x x x x x x x
MAX := $(foreach x,$(sixteen),$(sixteen))

# T estimates how many targets we are building by replacing BUILD with
# a special string
T := $(shell $(MAKE) -nrRf $(firstword $(MAKEFILE_LIST)) $(MAKECMDGOALS) \
            BUILD="COUNTTHIS" | grep -c "COUNTTHIS")

# N is the number of pending targets in base 1, well in fact, base x
# :-)
N := $(wordlist 1,$T,$(MAX))

# auto-decrementing counter that returns the number of pending targets
# in base 10
counter = $(words $N)$(eval N := $(wordlist 2,$(words $N),$N))

# BUILD is now defined to show the progress, this also avoids
# redefining T in loop
BUILD = @echo $(counter) of $(T)
endif
################################################################################

all: dirs $(EXE)
	# Build successful!

$(EXE): $(OBJECTS) $(LIBS_OBJECTS)
	# Linking...
	$(MUTE)$(CXX) $(OBJECTS) $(LIBS_OBJECTS) -o $(EXE) $(LDFLAGS)

# This needed to be added manually
src/lib/SDL_Config/SDL_config.o: src/lib/SDL_Config/SDL_config.c
	# Compiling $<...
	$(MUTE)$(CXX) $< -c -o $@ $(INCLUDE) -fexpensive-optimizations -O3

src/%.o: src/%.cpp
	# Compiling $<...
	$(MUTE)$(CXX) $(CXXFLAGS) $(INCLUDE) $< -c -o $@
	$(BUILD)

src/%.o: src/%.c
	# Compiling $<...
	$(MUTE)$(CC) $(CFLAGS) $(INCLUDE) $< -c -o $@

run: all
	$(MUTE)./$(EXE)

clean:
	# Cleaning...
	-$(MUTE)rm -f $(EXE) $(OBJECTS)

libclean: clean
	# Cleaning libs...
	-$(MUTE)rm -f $(LIBS_OBJECTS)

dirs:
	$(MUTE)mkdir -p img map src

# Generates full documentation for the project
dox:
	$(MUTE)doxygen Doxyfile
	# Documentation generated!

doxclean:
	$(MUTE)rm -rf doc/html
	# Documentation cleaned!


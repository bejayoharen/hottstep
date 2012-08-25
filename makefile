
SO_NAME:=libhottstepsynth.so.1
SO_LIB:=libhottstepsynth.so.1.0.0
STATIC_LIB:=libhottsetpsynth.a

CPPFILES:=src/LoopData.cpp src/SequencePlayer.cpp
OBJECTS:=build/target/SequencePlayer.opp
HEADERS:=src/LoopData.h src/SequencePlayer.h

CFLAGS=-fPIC -O2 -fvisibility=hidden -fvisibility-inlines-hidden
CPPFLAGS=$(CFLAGS)
LINK_FLAGS=
CC=gcc
CPP=g++
#SHARED=$(CPP) -shared -Wl,-soname,$(SO_NAME)
SHARED=$(CPP) -shared -Wl,-install_name,$(SO_NAME)
TESTS=build/bin/Test

#everything!
tests: all $(TESTS)

#libraries
all: build/lib/$(STATIC_LIB) build/lib/$(SO_LIB)
	-mkdir build/include
	cp src/*.h build/include

build/lib/$(STATIC_LIB): $(OBJECTS) build/lib
	ar rcs build/lib/$(STATIC_LIB) $(OBJECTS)

build/lib/$(SO_LIB): $(OBJECTS) build/lib
	$(SHARED) $(LINK_FLAGS) -o build/lib/$(SO_LIB)  $(OBJECTS)

#object files
build/target/%.opp: src/%.cpp build/target $(HEADERS)
	$(CPP) $(CPPFLAGS) -c $< -o $@

# tests
build/bin/% : test/%.cpp all build/bin
	$(CPP) $(CPPFLAGS) $(LINK_FLAGS) -I include -I build/include $< -o $@ build/lib/$(STATIC_LIB) libs/*.a -framework CoreAudio -framework AudioToolbox -framework AudioUnit -framework CoreServices

# make folders
build:
	-mkdir build

build/bin: build
	-mkdir build/bin

build/lib: build
	-mkdir build/lib

build/target: build
	-mkdir build/target

#utilities
edit:
	gvim src/*.h
	gvim src/*.cpp
	gvim test/*.cpp

doc: clean
	(cd  src/ ; doxygen ../doxyfile )

clean :
	-rm -r doc
	-rm -r build
	-rm $(OBJECTS)

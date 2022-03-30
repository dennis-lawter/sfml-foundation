rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

EXECUTABLE=sfmlfoundation

CC=C:/cppdev/mingw-w64-7.3.0/mingw64/bin/g++.exe
CFLAGS=-O0 -g -Wall -c -fmessage-length=0 -std=c++17 -Wl,--subsystem,windows
LIBRARYDIR="-LC:/cppdev/SFML-2.5.1/lib"
LIBRARIES=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
INCLUDEDIR="-IC:/cppdev/SFML-2.5.1/include"

RM=C:/cppdev/msys/bin/rm.exe
CP=C:/cppdev/msys/bin/cp.exe
MKDIR=C:/cppdev/msys/bin/mkdir.exe

dir_guard=$(MKDIR) -p $(@D)

SRC_DIR=src/
DEBUG_OBJ_DIR=Obj_Debug/
DEBUG_OUT_DIR=Debug/
RES_DIR=res/resource

DLLS=\
"C:/cppdev/SFML-2.5.1/bin/sfml-audio-2.dll" \
"C:/cppdev/SFML-2.5.1/bin/sfml-graphics-2.dll" \
"C:/cppdev/SFML-2.5.1/bin/sfml-system-2.dll" \
"C:/cppdev/SFML-2.5.1/bin/sfml-window-2.dll" \
"C:/cppdev/SFML-2.5.1/bin/openal32.dll" \
"C:/cppdev/mingw-w64-7.3.0/mingw64/bin/libstdc++-6.dll" \
"C:/cppdev/mingw-w64-7.3.0/mingw64/bin/libwinpthread-1.dll" \
"C:/cppdev/mingw-w64-7.3.0/mingw64/bin/libgcc_s_seh-1.dll" 

CPPSOURCES=$(call rwildcard,src/,*.cpp)
CCSOURCES=$(call rwildcard,src/,*.cc)
SOURCES= $(CPPSOURCES) $(CCSOURCES)

TEMP=$(SOURCES:.cpp=.o)
OBJECTS=$(TEMP:.cc=.o)
OBJECTSOUT=$(OBJECTS:$(SRC_DIR)%=$(DEBUG_OBJ_DIR)%)

all: $(DEBUG_OUT_DIR)$(EXECUTABLE)

copyresources:
	$(CP) -R $(RES_DIR) $(DEBUG_OUT_DIR)

$(DEBUG_OUT_DIR)$(EXECUTABLE): $(OBJECTSOUT)
	$(dir_guard)
	$(CC) $(LIBRARYDIR) -o $@ $(OBJECTSOUT) $(LIBRARIES)
	$(CP) $(DLLS) $(RELEASE_OUT_DIR)

$(DEBUG_OBJ_DIR)%.o: $(SRC_DIR)%.cc
	$(dir_guard)
	$(CC) $(LIBRARIES) $(CFLAGS) $(INCLUDEDIR) -c $< -o $(@:src/%=debug/%)

$(DEBUG_OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(dir_guard)
	$(CC) $(LIBRARIES) $(CFLAGS) $(INCLUDEDIR) -c $< -o $(@:src/%=debug/%)

clean:
	$(RM) -rf $(DEBUG_OUT_DIR)
	$(RM) -rf $(DEBUG_OBJ_DIR)

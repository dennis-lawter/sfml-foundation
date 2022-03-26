rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

EXECUTABLE=sfmlfoundation

CC=g++
CFLAGS=-O0 -g -Wall -c -fmessage-length=0 -std=c++17 -Wl,--subsystem,windows
LINKFLAGS=-pthread
LIBRARIES=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

RM=rm
CP=cp
MKDIR=mkdir

dir_guard=$(MKDIR) -p $(@D)

SRC_DIR=src/
DEBUG_OBJ_DIR=Obj_Debug/
DEBUG_OUT_DIR=Debug/

CPPSOURCES=$(call rwildcard,src/,*.cpp)
CCSOURCES=$(call rwildcard,src/,*.cc)
SOURCES= $(CPPSOURCES) $(CCSOURCES)

TEMP=$(SOURCES:.cpp=.o)
OBJECTS=$(TEMP:.cc=.o)
OBJECTSOUT=$(OBJECTS:$(SRC_DIR)%=$(DEBUG_OBJ_DIR)%)

all: $(DEBUG_OUT_DIR)$(EXECUTABLE)

$(DEBUG_OUT_DIR)$(EXECUTABLE): $(OBJECTSOUT)
	$(dir_guard)
	$(CC) $(LINKFLAGS) $(LIBRARYDIR) -o $@ $(OBJECTSOUT) $(LIBRARIES)
	$(CP) -R res/resource $(DEBUG_OUT_DIR)

$(DEBUG_OBJ_DIR)%.o: $(SRC_DIR)%.cc
	$(dir_guard)
	$(CC) $(LIBRARIES) $(CFLAGS) $(INCLUDEDIR) -c $< -o $(@:src/%=debug/%)

$(DEBUG_OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(dir_guard)
	$(CC) $(LIBRARIES) $(CFLAGS) $(INCLUDEDIR) -c $< -o $(@:src/%=debug/%)

clean:
	$(RM) -rf $(DEBUG_OUT_DIR)
	$(RM) -rf $(DEBUG_OBJ_DIR)

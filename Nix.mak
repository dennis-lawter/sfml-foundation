rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

EXECUTABLE=GameName

RM=rm
CP=cp
MKDIR=mkdir
CC=g++
CFLAGS=-O1 -Wall -c -fmessage-length=0 -std=c++17
LIBRARIES=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

dir_guard=$(MKDIR) -p $(@D)

SRC_DIR=src/
RELEASE_OBJ_DIR=Obj_Release/
RELEASE_OUT_DIR=Release/

CPPSOURCES=$(call rwildcard,src/,*.cpp)
CCSOURCES=$(call rwildcard,src/,*.cc)
SOURCES= $(CPPSOURCES) $(CCSOURCES)

TEMP=$(SOURCES:.cpp=.o)
OBJECTS=$(TEMP:.cc=.o)
OBJECTSOUT=$(OBJECTS:$(SRC_DIR)%=$(RELEASE_OBJ_DIR)%)

all: $(RELEASE_OUT_DIR)$(EXECUTABLE)

$(RELEASE_OUT_DIR)$(EXECUTABLE): $(OBJECTSOUT)
	$(dir_guard)
	$(CC) $(LIBRARYDIR) -o $@ $(OBJECTSOUT) $(LIBRARIES)
	$(CP) -R res/resource $(RELEASE_OUT_DIR)

$(RELEASE_OBJ_DIR)%.o: $(SRC_DIR)%.cc
	$(dir_guard)
	$(CC) $(LIBRARIES) $(CFLAGS) $(INCLUDEDIR) -c $< -o $(@:src/%=release/%)

$(RELEASE_OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(dir_guard)
	$(CC) $(LIBRARIES) $(CFLAGS) $(INCLUDEDIR) -c $< -o $(@:src/%=release/%)

clean:
	$(RM) -rf $(RELEASE_OUT_DIR)
	$(RM) -rf $(RELEASE_OBJ_DIR)


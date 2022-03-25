rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

EXECUTABLE=GameName

RM=rm
CP=cp
MKDIR=mkdir
CC=g++
CFLAGS=-O3 -Wall -c -fmessage-length=0 -std=c++17
LIBRARIES=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

dir_guard=$(MKDIR) -p $(@D)

SRC_DIR=src/
RELEASE_OBJ_DIR=Obj_Release/
RELEASE_OUT_DIR=Release/
RELEASE_ZIP=TotallyInvadingSpace.tar.gz

ZIP=tar
ZIPFLAGS=czf


DLLS=\
/usr/lib/x86_64-linux-gnu/libsfml-audio.so \
/usr/lib/x86_64-linux-gnu/libsfml-graphics.so \
/usr/lib/x86_64-linux-gnu/libsfml-system.so \
/usr/lib/x86_64-linux-gnu/libsfml-window.so \
/usr/lib/x86_64-linux-gnu/libopenal.so.1

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
	$(CP) $(DLLS) $(RELEASE_OUT_DIR)
	$(RM) $(RELEASE_OUT_DIR)resource/HighScore.txt

$(RELEASE_OBJ_DIR)%.o: $(SRC_DIR)%.cc
	$(dir_guard)
	$(CC) $(LIBRARIES) $(CFLAGS) $(INCLUDEDIR) -c $< -o $(@:src/%=release/%)

$(RELEASE_OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(dir_guard)
	$(CC) $(LIBRARIES) $(CFLAGS) $(INCLUDEDIR) -c $< -o $(@:src/%=release/%)

clean:
	$(RM) -rf $(RELEASE_OUT_DIR)
	$(RM) -rf $(RELEASE_OBJ_DIR)
	$(RM) -rf $(RELEASE_ZIP)

zip:
	$(ZIP) $(ZIPFLAGS) $(RELEASE_ZIP) $(RELEASE_OUT_DIR)

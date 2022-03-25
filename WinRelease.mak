rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

EXECUTABLE=sfmlfoundation
FINALEXE=GameName

CC=C:/cppdev/mingw-w64-7.3.0/mingw64/bin/g++.exe
CFLAGS=-O3 -Wall -c -fmessage-length=0 -std=c++17 -mwindows -Wl,-subsystem,windows
LIBRARYDIR="-LC:/cppdev/SFML-2.5.1/lib"
LIBRARIES=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
INCLUDEDIR="-IC:/cppdev/SFML-2.5.1/include"

RM=C:/cppdev/msys/bin/rm.exe
CP=C:/cppdev/msys/bin/cp.exe
MKDIR=C:/cppdev/msys/bin/mkdir.exe

dir_guard=$(MKDIR) -p $(@D)

SRC_DIR=src/
RELEASE_OBJ_DIR=Obj_Release/
RELEASE_OUT_DIR=Release/
RELEASE_ZIP="TotallyInvadingSpace.zip"

RESHACK=C:/cppdev/ResourceHacker/ResourceHacker.exe
RESHACKFLAGS=-open $(RELEASE_OUT_DIR)$(EXECUTABLE).exe -save "$(RELEASE_OUT_DIR)$(FINALEXE).exe" -action addskip -res res/resource/player.ico -mask ICONGROUP,MAINICON,

ZIP=powershell Compress-Archive
ZIPFLAGS=$(RELEASE_OUT_DIR) $(RELEASE_ZIP)

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

reshack:
	$(RESHACK) $(RESHACKFLAGS)
	$(RM) $(RELEASE_OUT_DIR)$(EXECUTABLE).exe

zip:
	$(ZIP) $(ZIPFLAGS)

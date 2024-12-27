CC = gcc
CXX = g++
WINDRES = windres
MINGW_DIR = C:/mingw32
FREEGLUT_DIR = C:/freeglut

CFLAGS = -I$(FREEGLUT_DIR)/include
CXXFLAGS = -I$(FREEGLUT_DIR)/include
LDFLAGS = -L$(FREEGLUT_DIR)/lib -lfreeglut -lopengl32 -lglu32 -lgdi32 -mwindows

SRC_DIR = source
OBJ_DIR = obj
BIN_DIR = release

# znajdź wszystkie pliki (*.c; *.cpp)
C_SOURCES = $(wildcard $(SRC_DIR)/*.c)
CPP_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# konwertuj pliki c na pliki obj
C_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(C_SOURCES))
CPP_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(CPP_SOURCES))

OBJS = $(C_OBJS) $(CPP_OBJS) $(OBJ_DIR)/snek.res

.PHONY: all clean

all: $(BIN_DIR)/SNEK.exe $(BIN_DIR)/AboutDialog.dll

$(BIN_DIR)/SNEK.exe: $(OBJS)
    $(CC) -o $@ $^ $(LDFLAGS)

$(BIN_DIR)/AboutDialog.dll: $(SRC_DIR)/AboutDiag/AboutDiag.cpp
    $(CXX) -shared -o $@ $< -lgdi32

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
    $(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
    $(CXX) -c -o $@ $< $(CXXFLAGS)

$(OBJ_DIR)/snek.res: $(SRC_DIR)/snek.rc
    $(WINDRES) $< -O coff -o $@

clean:
    rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/*.res $(BIN_DIR)/SNEK.exe $(BIN_DIR)/AboutDialog.dll

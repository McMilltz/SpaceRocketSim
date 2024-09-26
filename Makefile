GXX = g++
GXXFLAGS = -Wall 
OUT = ./out/Rocket

LINK_SDL = -lSDL2
LINK_MATH = -lm
LINK_IMG = -lSDL2_image
LINKS = $(LINK_SDL) $(LINK_MATH) $(LINK_IMG)

SRC_DIR = ./src
SRC_SUB = $(wildcard $(SRC_DIR)/*/*.cpp) $(wildcard $(SRC_DIR)/*/*.hpp)
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*.hpp)

all: $(SRCS) $(SRC_SUB)
	$(GXX) $(GXXFLAGS) $^ $(LINKS) -o $(OUT)

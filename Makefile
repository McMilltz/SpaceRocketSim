GXX = g++
GXXFLAGS = -Wall 
OUT = ./out/Rocket

LINK_SDL = -lSDL2
LINK_MATH = -lm
LINK_IMG = -lSDL2_image
LINKS = $(LINK_SDL) $(LINK_MATH) $(LINK_IMG)

SRC_DIR = ./src
SRCS = $(wildcard $(SRC_DIR)/*.cpp)


all: $(SRCS)
	$(GXX) $(GXXFLAGS) $^ $(LINKS) -o $(OUT)

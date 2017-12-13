CC = g++
SOURCE_DIR = source/
MAIN_FILE = $(SOURCE_DIR)main.cpp $(SOURCE_DIR)body.cpp $(SOURCE_DIR)/utils/RGBpixmap.cpp
FINAL_FILE = main
CLIBS = -framework OpenGL -framework GLUT -Wno-deprecated-declarations
all:
	$(CC) $(CLIBS) $(MAIN_FILE) -o $(FINAL_FILE)
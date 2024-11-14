# Definujte proměnné
CC = g++
CFLAGS = -pthread -std=c++17
FILE_NAME = main
INCLUDES = -I/usr/include -I/usr/include/opencv4
OPENCV_LIBS = -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio -lopencv_objdetect -lopencv_imgcodecs
GLFW_LIBS = -lglfw -lGL -lXrandr -lXi -lXinerama -lX11 -lrt -ldl

# Set the LIBS variable to the sum of the OPENCV_LIBS and GLFW_LIBS variables
LIBS = $(OPENCV_LIBS) $(GLFW_LIBS)
TARGET = $(FILE_NAME).out
SRC = $(FILE_NAME).cpp

# Výchozí cíl
all: $(TARGET)

# Pravidlo pro sestavení programu
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(SRC) $(LIBS)

# Pravidlo pro vyčištění sestavení
clean:
	rm -f $(TARGET) *.o

# Pravidlo pro spuštění programu
run: $(TARGET)
	./$(TARGET)
# Definujte proměnné
CC = g++
CFLAGS = -Wall -g -std=c++17
INCLUDES = -I/usr/include/opencv4
LIBS = -L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio -lopencv_objdetect -lopencv_imgcodecs
TARGET = app.out

# Výchozí cíl
all: $(TARGET)

# Pravidlo pro sestavení programu
$(TARGET): App.cpp
	$(CC) $(CFLAGS) $(INCLUDES) App.cpp -o $(TARGET) $(LIBS)

# Pravidlo pro vyčištění sestavení
clean:
	rm -f $(TARGET) *.o

# Pravidlo pro spuštění programu
run: $(TARGET)
	./$(TARGET)
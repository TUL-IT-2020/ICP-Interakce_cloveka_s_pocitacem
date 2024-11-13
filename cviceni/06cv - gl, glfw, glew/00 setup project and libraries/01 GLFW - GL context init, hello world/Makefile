# Definujte proměnné
CC = g++
CFLAGS = -pthread
INCLUDES = -I/usr/include
#LIBS = -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl
LIBS = -lglfw -lGL -lXrandr -lXi -lXinerama -lX11 -lrt -ldl
TARGET = test.out
SRC = test.cpp

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
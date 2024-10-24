# Definujte proměnné
CC = g++
CFLAGS = -Wall -g
MAIN = $(main)

# Výchozí cíl
all: program

# Pravidlo pro sestavení programu
program: $(MAIN)
	$(CC) $(CFLAGS) -o program $(MAIN)

# Pravidlo pro vyčištění sestavení
clean:
	rm -f program *.o
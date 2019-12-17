CC=gcc
CFLAGS=
LDFLAGS=
EXEC=tri

all: $(EXEC)

tri: tri.o
	$(CC) -o $@ $^ $(LDFLAGS) -lSDL

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) -lSDL

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
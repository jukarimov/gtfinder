
all = gtfinder

LIBS = $(shell pkg-config gtk+-2.0 --libs)
CFLAGS = $(shell pkg-config gtk+-2.0 --cflags)

OBJS = gtfinder.o box.o file_chooser.o list.o

%.o: %.c
	$(CC) $(LIBS) $(CFLAGS) -c $< -o $@

gtfinder: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean: 
	rm -f *.o gtfinder

